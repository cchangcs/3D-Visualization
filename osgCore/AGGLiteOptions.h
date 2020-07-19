#pragma once
#pragma once
#ifndef OSGEARTH_DRIVER_AGGLITE2_DRIVEROPTIONS
#define OSGEARTH_DRIVER_AGGLITE2_DRIVEROPTIONS 1
#include <osgEarth/Common>
#include <osgEarthFeatures/FeatureTileSource>

namespace osgEarth {
	namespace Drivers
	{
		using namespace osgEarth;
		using namespace osgEarth::Features;

		class AGGLiteOptions2 : public FeatureTileSourceOptions // NO EXPORT; header only
		{
		public:
			/**
			* Whether to downsample line features to that they are no higher resolution than
			* the target image resolution. Defaults to true, but you can disable this (for a possible
			* performance increase) if you know your data to be of a relatively low resolution.
			* (Default = true)
			*/
			optional<bool>& optimizeLineSampling() { return _optimizeLineSampling; }
			const optional<bool>& optimizeLineSampling() const { return _optimizeLineSampling; }

			/**
			* Set the gamma parameter applied on the AggLite rasterizer : allow to control geometry antialiasing
			* (Default = 1.3)
			*/
			optional<double>& gamma() { return _gamma; }
			const optional<double>& gamma() const { return _gamma; }

			//w.g.描边的颜色和宽度(单位像素)
			/** Border color. */
			Color& borderColor() { return _borderColor; }
			const Color& borderColor() const { return _borderColor; }
			/** Line border rendering width. */
			optional<double>& borderWidth() { return _borderWidth; }
			const optional<double>& borderWidth() const { return _borderWidth; }

		public:
			AGGLiteOptions2(const TileSourceOptions& options = TileSourceOptions())
				: FeatureTileSourceOptions(options),
				_optimizeLineSampling(true),
				_gamma(1.3),
				_borderColor(Color::White),
				_borderWidth(1)
			{
				setDriver("agglite2");
				fromConfig(_conf);
			}

			/** dtor */
			virtual ~AGGLiteOptions2() { }

		public:
			Config getConfig() const {
				Config conf = FeatureTileSourceOptions::getConfig();
				conf.updateIfSet("optimize_line_sampling", _optimizeLineSampling);
				conf.updateIfSet("gamma", _gamma);
				conf.add("borderColor", _borderColor.toHTML());
				conf.updateIfSet("borderWidth", _borderWidth);
				return conf;
			}

		protected:
			void mergeConfig(const Config& conf) {
				FeatureTileSourceOptions::mergeConfig(conf);
				fromConfig(conf);
			}

		private:
			void fromConfig(const Config& conf) {
				conf.getIfSet("optimize_line_sampling", _optimizeLineSampling);
				conf.getIfSet("gamma", _gamma);
				_borderColor = Color(conf.value("borderColor"));
				conf.getIfSet("borderWidth", _borderWidth);
			}

			optional<bool>   _optimizeLineSampling;
			optional<double> _gamma;
			//w.g.描边的颜色和宽度(单位像素)
			Color            _borderColor;
			optional<double>  _borderWidth;
		};

	}
} // namespace osgEarth::Drivers

#endif // OSGEARTH_DRIVER_AGGLITE2_DRIVEROPTIONS