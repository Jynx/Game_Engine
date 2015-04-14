#include "ImageLoader.h"
#include "IOManager.h"
#include "Errors.h"

namespace Sengine {
	OpenGLTexture ImageLoader::LoadImageFromFile(const std::string& filename,
		int channelOptions,
		unsigned int reuseID,
		unsigned int flags) {
		OpenGLTexture texture = {};
		GLuint tex_id =
			SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (!tex_id) {
			FatalError("Could not create texture ID from " + filename + "\n");
		}
		int img_width, img_height;
		unsigned char* imgPtr =
			SOIL_load_image(filename.c_str(), &img_width, &img_height, NULL, 0);
		if (!imgPtr) {
			FatalError("Could not extra image data with " + filename + "\n");
		}
		texture.ID = tex_id;
		texture.height = img_height;
		texture.width = img_width;

		// generate 1 texture, ptr to gluint.
		glGenTextures(1, &texture.ID);
		// bind the texture 1:type of texture, 2:what texture to bind.
		glBindTexture(GL_TEXTURE_2D, texture.ID);
		// 2: mip map level, 3:format 5: border (border around?) 6: format of
		// pixels, 7 type of data, 8 pointer to data.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, imgPtr);
		// 1: effect GL texture 2d, 2: how do you want texture to wrap on an image
		// can be repeated, clamped etc.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// based on size of texture, linear interpolation? filter types.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

	/* unsigned char* buffer = nullptr;
		// char path[256];
		// GetCurrentDirectory(path, 256

		// load image into memory
		// int bufSize = 0;
		/*if (!(IOManager::ReadFileToBuf(buffer, filename, bufSize))) {
		FatalError("Failed to load: " + filename + "in LoadImage");
		}
		// load image to temporary memory, and obtain image data(w/h etc.)
		int width, height, channels;
		unsigned char* ptr = SOIL_load_image_from_memory(
		buffer, bufSize, &width, &height, &channels, channelOptions);

		if (ptr) {
		// copy data into pixel buffer based on ptr size.
		unsigned char* tmpBuff = new unsigned char[width * height];
		buffer = tmpBuff;
		delete[] tmpBuff;
		// width * height * 4 bits per pointer
		memcpy(&buffer[0], ptr, width * height * 4);
		// delete[] ptr;
		// SOIL_free_image_data(ptr);

		} else {
		FatalError("Could not load image from memory in LoadImageFromMemory");
		}

		GLuint id = SOIL_load_OGL_texture("body_3Dblue.png", SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		// SOIL_create_OGL_texture(buffer, width, height, channels,
		//                              reuseID, flags);
		/* if (!id) {
		FatalError("Could not create OpenGL Texture ID from image memory");
		}

		*/

}