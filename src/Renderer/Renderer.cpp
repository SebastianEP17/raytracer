#include "Renderer.hpp"
#include "logger/Logger.hpp"
#include "Math/Random.hpp"
#include "Shape/Material/Material.hpp"

#include <format>

#include "Math/Mat.hpp"

namespace raytracer
{

    namespace renderer
    {
        std::atomic<size_t> totalComputedPixels {0};
    }

    Renderer::Renderer
    (
        const yml::Yml& yml
    )
        : _camera(Camera::fromConfig(yml)),
          _scene(yml),
          _settings{}
    {
        yml::Node resolutionNode = yml["camera"]["resolution"];

        this->_width = resolutionNode["width"].as<int>();
        this->_height = resolutionNode["height"].as<int>();
        this->_settings.antiAliasingSamples = resolutionNode["antialiasingSamples"].as<int>();
        this->_settings.maxBounces = resolutionNode["maxBounces"].as<int>();

        this->_render = std::make_unique<image::Ppm>(this->_width, this->_height);

        LOG_DEBUG(std::format(
            "Renderer successfully loaded. ({}x{}, {}, Maximum bounces: {})",
            this->_width, this->_height,
            this->_settings.antiAliasingSamples, this->_settings.maxBounces
        ));
    }

    void
    Renderer::render
    (
        const uint32_t x, const uint32_t y,
        const uint32_t width, const uint32_t height,
        const std::atomic<bool>& shouldStop
    )
        const
    {
        if (x > this->_width || y > this->_height ||
            width + x > this->_width || height + y > this->_height) {
            LOG_FATAL(std::format(
                "Rectangle to render is out of bounds.\n"
                "x: {}, y: {}, width: {}, height: {}.",
                x, y, width, height
            ));
            return;
        }

        LOG_DEBUG(std::format(
            "Rendering image: x: {} y: {} width: {} height: {}",
            x, y, width, height
        ));

        for (uint32_t j = y; j <= y + height; j++) {
            for (uint32_t i = x; i < x + width; i++) {
                math::Color pixelColor;

                for (size_t spl = 0; spl < this->_settings.antiAliasingSamples; spl++) {
                    if (shouldStop.load() == true) {
                        return;
                    }

                    const double u = (i + math::randomDouble()) / this->_width;
                    const double v = (j + math::randomDouble()) / this->_height;

                    math::Ray ray = this->_camera.ray(u, v);
                    pixelColor += computeColor(ray, this->_settings.maxBounces);
                }

                pixelColor *= 1.0 / static_cast<double>(this->_settings.antiAliasingSamples);
                pixelColor.clamp(0.0, 1.0);

                this->_render->setAt(i, j, pixelColor);
                renderer::totalComputedPixels.fetch_add(1);
            }
        }
    }

    void
    Renderer::render
    (
        const renderer::Tile &tile,
        const std::atomic<bool> &shouldStop
    )
        const
    {
        this->render(tile.x, tile.y, tile.width, tile.height, shouldStop);
    }

    math::Color
    Renderer::computeColor
    (
        const math::Ray &ray,
        size_t bounces
    )
        const
    {
        if (bounces == 0) {
            return {}; // Pure black
        }

        HitResult res{};

        if (this->_scene.hits(ray, res)) {
            math::Ray scattered;
            math::Color attenuation;

            if (res.material->scatter(ray, res, attenuation, scattered)) {
                const math::Color indirectLighting = computeColor(scattered, bounces - 1);
                const math::Color directLighting = computeDirectLighting(res);

                return attenuation * (indirectLighting + directLighting);
            }
            return {}; // Pure black
        }

        return {};

        // math::Vec<3> dir = ray.direction.normalized();
        // const double a = .5 * (dir[1] + 1);

        // return (1.0 - a) * math::Color(1, 1, 1) + a * math::Color(.5, .7, 1);
    }

    math::Color
    Renderer::computeDirectLighting
    (
        const HitResult &res
    )
        const
    {
        math::Color color;

        for (auto& light : this->_scene.getLights()) {
            math::Vec<3> directionToLight;
            double distanceToLight;
            const math::Color lightColor = light->sample(res.p, directionToLight, distanceToLight);

            if (light->isAmbient()) {
                color += lightColor;
                continue;
            }

            math::Ray shadowRay(res.p + ALMOST_ZERO * directionToLight, directionToLight);
            HitResult shadowHit;

            if (this->_scene.hits(shadowRay, shadowHit)) {
                if (shadowHit.t < distanceToLight) {
                    continue; // Blocked by an object
                }
            }

            const double nDotL = std::max(dot(res.n, directionToLight), 0.0);
            color += lightColor * nDotL;
        }
        return color;
    }

}
