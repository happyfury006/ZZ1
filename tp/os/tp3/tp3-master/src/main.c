#include <stdio.h>
#include <assert.h>
#include <utils.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION // Needs to be defined in one and ONLY one translation unit (.c)
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION // Needs to be defined in one and ONLY one translation unit (.c)
#include "stb_image_write.h"

bool NO_STDIO_BUFFERING = false;

typedef struct
{
    void *buffer;
    size_t size;
} SizedBuffer;

// Loads a full file into memory, any failure will trigger an assert and crash
SizedBuffer allocAndLoadFile(const char *filepath, const char *mode)
{
    FILE *f = fopen(filepath, mode);
    assert(f && "Failed to open file!");

    // No buffering
    if (NO_STDIO_BUFFERING)
        setvbuf(f, NULL, _IONBF, 0);


    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    void *data = malloc(fileSize);
    fseek(f, 0, SEEK_SET);
    int readBlocks = fread(data, fileSize, 1, f);
    assert(readBlocks == 1);
    fclose(f);

    SizedBuffer sb;
    sb.buffer = data;
    sb.size = fileSize;
    return sb;
}

int writeWholeFile(const char *filepath, SizedBuffer sb)
{
    FILE *f = fopen(filepath, "wb");

    if (NO_STDIO_BUFFERING)
        setvbuf(f, NULL, _IONBF, 0);

    if (!f)
        return 0;

    int writtenBlocks = fwrite(sb.buffer, sb.size, 1, f);
    assert(writtenBlocks == 1);
    fclose(f);
    return 1;
}

int main(int argc, char *argv[])
{

    if (argc <= 1)
    {
        printf("Usage: %s inimage1.jpg [inimage2.jpg]...\n", argv[0]);
        return 0;
    }

    NO_STDIO_BUFFERING = getenv("NO_STDIO_BUFFERING") != NULL;

    for (int i = 1; i < argc; i++)
    {
        const char *inFilePath = argv[i];
        char *outFilePath = utils_out_name("out", ".png", argv[i]);

        utils_timestamp startTime = utils_get_timestamp();

        // Read encoded image
        SizedBuffer rawFile = allocAndLoadFile(inFilePath, "rb");
        utils_timestamp afterfileloadTime = utils_get_timestamp();

        // Decode image to color buffer
        int x, y, channels;
        unsigned char *pixelData = stbi_load_from_memory(rawFile.buffer, rawFile.size, &x, &y, &channels, 0);
        utils_timestamp afterdecodeTime = utils_get_timestamp();

        // Encode color buffer to png
        SizedBuffer pngBuffer;
        int pngSize;
        pngBuffer.buffer = stbi_write_png_to_mem(pixelData, 0, x, y, channels, &pngSize);
        pngBuffer.size = pngSize;
        assert(pngBuffer.buffer != NULL);
        utils_timestamp afterencodeTime = utils_get_timestamp();

        // Write encoded png to file
        int ret = writeWholeFile(outFilePath, pngBuffer);
        utils_timestamp afterfilewriteTime = utils_get_timestamp();

        assert(ret != 0);
        STBIW_FREE(pngBuffer.buffer);
        free(outFilePath);

        printf("Timings:\n");
        printf("\tfileload duration: %fms\n", utils_timestamp_elapsed_ms(afterfileloadTime, startTime));
        printf("\tdecode duration:%fms\n", utils_timestamp_elapsed_ms(afterdecodeTime, afterfileloadTime));
        printf("\tencode duration:%fms\n", utils_timestamp_elapsed_ms(afterencodeTime, afterdecodeTime));
        printf("\tfilewrite duration:%fms\n", utils_timestamp_elapsed_ms(afterfilewriteTime, afterencodeTime));
        if(NO_STDIO_BUFFERING) printf("Buffering was disabled due to NO_STDIO_BUFFERING being\n");

    }
    return 0;
}
