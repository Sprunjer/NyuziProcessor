// 
// Copyright 2013 Jeff Bush
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 

#include "assert.h"
#include "TextureSampler.h"

TextureSampler::TextureSampler()
	:	fSurface(0)
{
}

void TextureSampler::bind(Surface *surface)
{
	fSurface = surface;

	assert((surface->getWidth() & (surface->getWidth() - 1)) == 0);
	assert((surface->getHeight() & (surface->getHeight() - 1)) == 0);
	fWidth = surface->getWidth();
	fHeight = surface->getHeight();
}

veci16 TextureSampler::readPixels(vecf16 u, vecf16 v)
{
	// Convert from texture space into raster coordinates
	veci16 tx = __builtin_vp_vftoi(u * splatf(fWidth)) & splati(fWidth - 1);
	veci16 ty = __builtin_vp_vftoi(v * splatf(fHeight)) & splati(fHeight - 1);
	
	return fSurface->readPixels(tx, ty);
}