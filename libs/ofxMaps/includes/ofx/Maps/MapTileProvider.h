//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "Poco/RegularExpression.h"
#include "ofJson.h"
#include "ofx/Maps/AbstractMapTypes.h"
#include "ofx/Maps/BaseProjection.h"
#include "ofx/Maps/SphericalMercatorProjection.h"
#include "ofx/Maps/TileCoordinate.h"


namespace ofx {
namespace Maps {


class TileKey;


/// \brief A MapTileProvider with default settings.
class MapTileProvider: public AbstractMapTileProvider
{
public:
    /// \brief Create a default MapTileProvider with no endpoint.
    MapTileProvider();

    /// \brief Create a MapTileProvider.
    /// \param URITemplates The collection of template URLs.
    /// \param minZoom The minimum zoom level supported by the provider.
    /// \param maxZoom The maximum zoom level supported by the provider.
    /// \param tileWidth The width of the provider's tiles in pixels.
    /// \param tileHeight The height of the provider's tiles in pixels.
    /// \param bounds The bounds of the provider.
    /// \param center The initial center for this provider.
    /// \param projection The projection used by the provider.
    MapTileProvider(const std::vector<std::string>& URITemplates,
                    int minZoom,
                    int maxZoom,
                    int tileWidth,
                    int tileHeight,
                    const Geo::CoordinateBounds& bounds,
                    const TileCoordinate& center,
                    const BaseProjection& projection);

    /// \brief Destroy the MapTileProvider.
    virtual ~MapTileProvider();

    virtual std::string id() const override;
    std::string name() const override;
    std::string description() const override;
    std::string attribution() const override;
    std::string version() const override;
    int minZoom() const override;
    int maxZoom() const override;
    float tileWidth() const override;
    float tileHeight() const override;
    glm::vec2 tileSize() const override;
    Geo::CoordinateBounds bounds() const override;
    TileCoordinate center() const override;
    double zoomForScale(double scale) const override;
    TileCoordinate geoToWorld(const Geo::Coordinate& location) const override;
    Geo::Coordinate tileToGeo(const TileCoordinate& coordinate) const override;
    std::string getTileURI(const TileKey& coordinate) const override;
    bool isCacheable() const override;

    /// \returns the URI templates.
    const std::vector<std::string> URITemplates() const;

    /// \returns a collection of name value-pairs used used by this provider.
    std::map<std::string, std::string> dictionary() const;

    enum
    {
        /// \brief The minimum zoom level supported by most map tile providers.
        DEFAULT_MIN_ZOOM = 0,
        /// \brief The maximum zoom level supported by most map tile providers.
        DEFAULT_MAX_ZOOM = 22,
        /// \brief The default tile width supported by most map tile providers.
        DEFAULT_TILE_WIDTH = 256,
        /// \brief The default tile height supported by most map tile providers.
        DEFAULT_TILE_HEIGHT = 256
    };

    /// \brief The default map bounds.
    static const Geo::CoordinateBounds DEFAULT_BOUNDS;

    /// \brief The default map center.
    static const TileCoordinate DEFAULT_CENTER;

    /// \brief The default projection used by most map tile providers.
    static const SperhicalMercatorProjection DEFAULT_PROJECTION;

    /// \brief Create a MapTileProvider from JSON.
    ///
    /// This parses the JSON in the TileJSON 2.1.0 format. Not all features
    /// are supported.
    ///
    /// \param json The json to parse.
    /// \returns a configured MapTileProvider.
    /// \sa https://github.com/mapbox/tilejson-spec/tree/master/2.1.0
    static MapTileProvider fromJSON(const ofJson& json);

    /// \brief Export the MapTileProvider as JSON.
    ///
    /// This exports the provider in a TileJSON 2.1.0 format. Not all features
    /// are supported.
    ///
    /// \param provider The provider to save.
    /// \returns the json..
    /// \sa https://github.com/mapbox/tilejson-spec/tree/master/2.1.0
    static ofJson toJSON(const MapTileProvider& provider);

protected:
    /// \brief Extracts a template parameter value if it is available.
    ///
    /// This class should be overriden if the provider uses additional URI
    /// template variables.
    ///
    /// \param coordinate The tile coordinate requested.
    /// \param templateParameter The template parameter requested.
    /// \param templateValue The extracted value to be filled.
    /// \returns true iff the extraction was successful.
    virtual bool getTileURITemplateValue(const TileKey& key,
                                         const std::string& templateParameter,
                                         std::string& templateValue) const;

    /// \brief The URI template used for extraction.
    std::vector<std::string> _URITemplates;

    /// \brief A collection of URI template parameters for each of the templates.
    std::vector<std::vector<std::string>> _URITemplateParameters;

private:
    void _setURITemplates(const std::vector<std::string>& templates);

    /// \brief A unique ID for the provider, based on the URI template.
    std::string _id;

    /// \brief This provider's name.
    std::string _name;

    /// \brief This provider's description.
    std::string _description;

    /// \brief A string containing this provider's attribution.
    std::string _attribution;

    /// \brief A string containing this provider's data version.
    std::string _version;

    /// \brief The minimum zoom level for this provider.
    int _minZoom;

    /// \brief The maximum zoom level for this provider.
    int _maxZoom;

    /// \brief The tile width and height used by this provider.
    glm::ivec2 _tileSize;

    /// \brief The bounds for this provider.
    Geo::CoordinateBounds _bounds;

    /// \brief The initial center for this provider.
    TileCoordinate _center;

    /// \brief A reference to this provider's projection.
    const BaseProjection& _projection;

    /// \brief A dictionary of unknown parameters that can be used for template matching.
    std::map<std::string, std::string> _dictionary;

};


} } // namespace ofx::Maps
