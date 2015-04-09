#include "ImageLoader.h"
#include "IOManager.h"
#include "Errors.h"

OpenGLTexture LoadImageFromMemory(const std::string& filename,
                                  int channelOptions, unsigned int reuseID,
                                  unsigned int flags) {
    OpenGLTexture texture = {};
    unsigned char* buffer = nullptr;

    // load image into memory
    if (!(IOManager::ReadFileToBuf(buffer, filename))) {
        FatalError("Failed to load: " + filename + "in LoadImage");
    }
    // load image to temporary memory, and obtain image data(w/h etc.)
    int width, height, channels;
    unsigned char* ptr = SOIL_load_image_from_memory(
        buffer, sizeof(buffer), &width, &height, &channels, channelOptions);

    if (ptr) {
        // copy data into pixel buffer based on ptr size.
        unsigned char* tmpBuff = new unsigned char[width * height];
        buffer = tmpBuff;
        delete[] tmpBuff;
        memcpy(&(buffer[0]), ptr, width * height * 4);
        SOIL_free_image_data(ptr);

    } else {
        FatalError("Could not load image from memory in LoadImageFromMemory");
    }

    GLuint id = SOIL_create_OGL_texture(buffer, width, height, channels,
                                        reuseID, flags);
    if (!id) {
        FatalError("Could not create OpenGL Texture ID from image memory");
    }
    texture.ID = id;
    texture.height = height;
    texture.width = width;
	
    // generate 1 texture, ptr to gluint.
    glGenTextures(1, &(texture.ID));
    // bind the texture 1:type of texture, 2:what texture to bind.
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    // 2: mip map level, 3:format 5: border (border around?) 6: format of
    // pixels, 7 type of data, 8 pointer to data.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, &(buffer[0]));
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
