#include <math.h>
#include "../include/perlin_noise.hpp"

float interpolate(float a0, float a1, float w)
{
	return (a1 - a0) * w + a0;
}

vector2 random_graident(int ix, int iy)
{
	// No precomputed gradients mean this works for any number of grid coordinates
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2; // rotation width
	unsigned a = ix, b = iy;
	a *= 3284157443;
	b ^= a << s | a >> w-s;
	b *= 1911520717;
	a ^= b << s | b >> w-s;
	a *= 2048419325;
	// what are these ~ used for???
	float random = a * (M_PI / ~(~0u >> 1));
	vector2 v;
	v.x = cos(random);
	v.y = sin(random);
	return v;
}

float dot_grid_gradient(int ix, int iy, float x, float y)
{
	// Get gradient from integer coordinates
	vector2 gradient = random_graident(ix, iy);
	
	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;
	
	// Compute the dot product
	return (dx * gradient.x + dy * gradient.y);
}

float perlin(float x, float y)
{
	// Determine grid cell coordinates
	int x0 = (int)floor(x);
	int x1 = x0 + 1;
	int y0 = (int)floor(y);
	int y1 = y0 + 1;
	
	// Determine interpolation weights
	float sx = x - (float)x0;
	float sy = y - (float)y0;
	
	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;
	
	n0 = dot_grid_gradient(x0, y0, x, y);
	n1 = dot_grid_gradient(x1, y0, x, y);
	ix0 = interpolate(n0, n1, sx);
	
	n0 = dot_grid_gradient(x0, y1, x, y);
	n1 = dot_grid_gradient(x1, y1, x, y);
	ix1 = interpolate(n0, n1, sx);
	
	value = interpolate(ix0, ix1, sy);
	return value;
}