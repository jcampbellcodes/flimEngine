#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "sb6.h"

// Wrapper to buffer users from the internal glfw driver
// Converted to enumeration for type safety - yeah!

enum AZUL_KEY
{
	/* Printable keys */
	KEY_SPACE           = 32,
	KEY_APOSTROPHE      = 39,  /* ' */
	KEY_COMMA           = 44,  /* , */
	KEY_MINUS           = 45,  /* - */
	KEY_PERIOD          = 46,  /* . */
	KEY_SLASH           = 47,  /* / */
	KEY_0               = 48,
	KEY_1               = 49,
	KEY_2               = 50,
	KEY_3               = 51,
	KEY_4               = 52,
	KEY_5               = 53,
	KEY_6               = 54,
	KEY_7               = 55,
	KEY_8               = 56,
	KEY_9               = 57,
	KEY_SEMICOLON       = 59,  /* ; */
	KEY_EQUAL           = 61,  /* = */
	KEY_A               = 65,
	KEY_B               = 66,
	KEY_C               = 67,
	KEY_D               = 68,
	KEY_E               = 69,
	KEY_F               = 70,
	KEY_G               = 71,
	KEY_H               = 72,
	KEY_I               = 73,
	KEY_J               = 74,
	KEY_K               = 75,
	KEY_L               = 76,
	KEY_M               = 77,
	KEY_N               = 78,
	KEY_O               = 79,
	KEY_P               = 80,
	KEY_Q               = 81,
	KEY_R               = 82,
	KEY_S               = 83,
	KEY_T               = 84,
	KEY_U               = 85,
	KEY_V               = 86,
	KEY_W               = 87,
	KEY_X               = 88,
	KEY_Y               = 89,
	KEY_Z               = 90,
	KEY_LEFT_BRACKET    = 91,  /* [ */
	KEY_BACKSLASH       = 92,  /* \ */
	KEY_RIGHT_BRACKET   = 93,  /* ] */
	KEY_GRAVE_ACCENT    = 96,  /* ` */
	KEY_WORLD_1         = 161, /* non-US #1 */
	KEY_WORLD_2         = 162, /* non-US #2 */

	KEY_ARROW_UP        = GLFW_KEY_UP,      
	KEY_ARROW_DOWN      = GLFW_KEY_DOWN,       
	KEY_ARROW_LEFT      = GLFW_KEY_LEFT ,    
	KEY_ARROW_RIGHT     = GLFW_KEY_RIGHT, 

	/* Function keys */
	KEY_ESCAPE          = GLFW_KEY_ESC,
	KEY_ENTER           = GLFW_KEY_ENTER,
	KEY_TAB             = GLFW_KEY_TAB,
	KEY_BACKSPACE       = GLFW_KEY_BACKSPACE,
	KEY_INSERT          = GLFW_KEY_INSERT,
	KEY_DELETE          = GLFW_KEY_DEL ,
	//KEY_RIGHT           = GLFW_KEY_RIGHT,
	//KEY_LEFT            = GLFW_KEY_LEFT,
	//KEY_DOWN            = GLFW_KEY_DOWN,
	//KEY_UP              = GLFW_KEY_UP,
	KEY_PAGE_UP         = GLFW_KEY_PAGEUP,
	KEY_PAGE_DOWN       = GLFW_KEY_PAGEDOWN,
	KEY_HOME            = GLFW_KEY_HOME,
	KEY_END             = GLFW_KEY_END,
	KEY_CAPS_LOCK       = GLFW_KEY_CAPS_LOCK,
	KEY_SCROLL_LOCK     = GLFW_KEY_SCROLL_LOCK,
	KEY_NUM_LOCK        = GLFW_KEY_KP_NUM_LOCK,
	// KEY_PRINT_SCREEN    = 283,
	KEY_PAUSE           = GLFW_KEY_PAUSE,
	KEY_F1              = GLFW_KEY_F1,
	KEY_F2              = GLFW_KEY_F2,
	KEY_F3              = GLFW_KEY_F3,
	KEY_F4              = GLFW_KEY_F4,
	KEY_F5              = GLFW_KEY_F5,
	KEY_F6              = GLFW_KEY_F6,
	KEY_F7              = GLFW_KEY_F7,
	KEY_F8              = GLFW_KEY_F8,
	KEY_F9              = GLFW_KEY_F9,
	KEY_F10             = GLFW_KEY_F10,
	KEY_F11             = GLFW_KEY_F11,
	KEY_F12             = GLFW_KEY_F12,
	KEY_F13             = GLFW_KEY_F13,
	KEY_F14             = GLFW_KEY_F14,
	KEY_F15             = GLFW_KEY_F15,
	KEY_F16             = GLFW_KEY_F16,
	KEY_F17             = GLFW_KEY_F17,
	KEY_F18             = GLFW_KEY_F18,
	KEY_F19             = GLFW_KEY_F19,
	KEY_F20             = GLFW_KEY_F20,
	KEY_F21             = GLFW_KEY_F21,
	KEY_F22             = GLFW_KEY_F22,
	KEY_F23             = GLFW_KEY_F23,
	KEY_F24             = GLFW_KEY_F24,
	KEY_F25             = GLFW_KEY_F25,
	KEY_KP_0            = GLFW_KEY_KP_0,
	KEY_KP_1            = GLFW_KEY_KP_1,
	KEY_KP_2            = GLFW_KEY_KP_2,
	KEY_KP_3            = GLFW_KEY_KP_3,
	KEY_KP_4            = GLFW_KEY_KP_4,
	KEY_KP_5            = GLFW_KEY_KP_5,
	KEY_KP_6            = GLFW_KEY_KP_6,
	KEY_KP_7            = GLFW_KEY_KP_7,
	KEY_KP_8            = GLFW_KEY_KP_8,
	KEY_KP_9            = GLFW_KEY_KP_9,
	KEY_KP_DECIMAL      = GLFW_KEY_KP_DECIMAL,
	KEY_KP_DIVIDE       = GLFW_KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY     = GLFW_KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT     = GLFW_KEY_KP_SUBTRACT,
	KEY_KP_ADD          = GLFW_KEY_KP_ADD,
	KEY_KP_ENTER        = GLFW_KEY_KP_ENTER,
	KEY_KP_EQUAL        = GLFW_KEY_KP_EQUAL,
	KEY_LEFT_SHIFT      = GLFW_KEY_LSHIFT,
	KEY_LEFT_CONTROL    = GLFW_KEY_LCTRL,
	KEY_LEFT_ALT        = GLFW_KEY_LALT,
	KEY_LEFT_SUPER      = GLFW_KEY_LSUPER,
	KEY_RIGHT_SHIFT     = GLFW_KEY_RSHIFT,
	KEY_RIGHT_CONTROL   = GLFW_KEY_RCTRL,
	KEY_RIGHT_ALT       = GLFW_KEY_RALT,
	KEY_RIGHT_SUPER     = GLFW_KEY_RSUPER,
	KEY_MENU            = GLFW_KEY_MENU,
};


class Keyboard
{
private:
	Keyboard();

	// Get the global access
	Keyboard *GetInstance();

public:	
	// Use this to read keyboard
	static bool GetKeyState( AZUL_KEY key );
};


#endif