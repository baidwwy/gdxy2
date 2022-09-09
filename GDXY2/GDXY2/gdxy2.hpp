#pragma once
#include "common.hpp"
#include <Image.hpp>
#include <Reference.hpp>
#include "ujpeg.h"

class GDXY2 : public godot::Reference {
	GODOT_CLASS(GDXY2, godot::Reference);

	uJPEG m_ujpeg;

	struct RGB {
		uint8_t R;	// 红色
		uint8_t G;	// 绿色
		uint8_t B;	// 蓝色
	};

	struct RGBA : RGB {
		uint8_t A;	// 通道
	};

	struct FrameHeader {
		int32_t key_x;			// 图片的锚点X
		int32_t key_y;			// 图片的锚点Y
		uint32_t width;			// 图片的宽度，单位像素
		uint32_t height;		// 图片的高度，单位像素
	};
public:
	static void _register_methods() {
		godot::register_method("read_mask", &GDXY2::read_mask);
		godot::register_method("read_mapx", &GDXY2::read_mapx);
		godot::register_method("read_jpeg", &GDXY2::read_jpeg);
		godot::register_method("read_was", &GDXY2::read_was);
		godot::register_method("format_pal", &GDXY2::format_pal);
		godot::register_method("string_id", &GDXY2::string_id);
	}

	void _init();

	PoolByteArray read_mapx(godot::PoolByteArray bytes);

	PoolByteArray read_jpeg(godot::PoolByteArray bytes);

	PoolByteArray read_mask(godot::PoolByteArray bytes, int width, int height);

	PoolByteArray read_was(godot::PoolByteArray bytes, godot::PoolByteArray pal);

	unsigned int string_id(godot::String s);

	PoolByteArray format_pal(godot::PoolByteArray pal);

	size_t decompress_mask(void* in, void* out);

	void jpeg_repair(uint8_t* Buffer, uint32_t inSize, uint8_t* outBuffer, uint32_t* outSize);

	void byte_swap(uint16_t& value);

	uint32_t set_alpha(RGBA Color, uint8_t Alpha);

	RGBA RGB565to888(uint16_t color, uint8_t Alpha = 255);
};

