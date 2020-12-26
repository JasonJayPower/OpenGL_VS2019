#pragma once

#include "STBImage.h"
#include "Types.h"

#include <glad/glad.h>
#include <memory>
#include <string>
#include <iostream>

struct PixelDeleter {
	void operator()(u8* pixels) const {
		if (pixels) {
			stbi_image_free(pixels);
		}
	}
};

struct Texture {
	u32 id;
	s32 width;
	s32 height;
	s32 bbp;
};


static Texture loadTexture(const std::string& file) {

	Texture tex;
	glGenTextures(1, &tex.id);
	glBindTexture(GL_TEXTURE_2D, tex.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::unique_ptr<u8, PixelDeleter> pixels(stbi_load(file.c_str(), &tex.width, &tex.height, 0, 0));

	if (pixels) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.get());
	} else {
		std::cout << "Failed to load pixels" << std::endl;
	}
	return tex;
}