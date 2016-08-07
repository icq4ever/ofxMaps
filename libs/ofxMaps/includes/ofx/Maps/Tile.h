// =============================================================================
//
// Copyright (c) 2014-2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ofPixels.h"
#include "ofTexture.h"


namespace ofx {
namespace Maps {


class Tile: public ofBaseDraws
{
public:
    enum class Type
    {
        RASTER
    };

    Tile(const ofPixels& pixels);

    virtual ~Tile();

    using ofBaseDraws::draw;

    void draw(float x, float y, float width, float height) const override;

    float getWidth() const override;
    float getHeight() const override;

    const ofPixels& pixels() const;
    const ofTexture& texture() const;

    Type type() const;

    bool hasTexture() const;
    void loadTexture();
    void clearTexture();

private:
    Type _type = Type::RASTER;
    ofPixels _pixels;
    ofTexture _texture;

};


} } // namespace ofx::Maps
