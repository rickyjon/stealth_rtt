extends Node

onready var stored = OS.get_window_size();
export var boundry = [Vector2(0,0), Vector2(1920*4,1080*2)];

func _input(event):
	#rewrite to C++/gdnative as a gdnative singleton (read up how to do that)
	if event.is_class("InputEventKey"):
		if event.is_pressed():
			if event.scancode == KEY_F11:
				OS.set_window_fullscreen(!OS.window_fullscreen);
				if !OS.window_fullscreen:
					OS.set_window_size(stored);
	pass;

func _ready():

	pass
