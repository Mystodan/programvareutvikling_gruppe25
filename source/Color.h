#pragma once

struct Color {
	/*
	 * DB
	 */
	int id;
	unsigned int hex_value;
	
	/*
	 * Non DB
	 */
	void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		hex_value = ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
			+ (a & 0xff);
	}

	// RRGGBBAA
	void set_color(unsigned int hex_color) {
		hex_value = hex_color;
	}

	uint8_t r() {
		return hex_value >> 24 & 0xFF;  // Extract the RR byte
	}
	uint8_t g() {
		return hex_value >> 16 & 0xFF;  // Extract the GG byte
	}
	uint8_t b() {
		return hex_value >> 8 & 0xFF;   // Extract the BB byte
	}
	uint8_t a() {
		return hex_value & 0xFF;        // Extract the AA byte
	}
};
