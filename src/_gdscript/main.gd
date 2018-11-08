extends Node

onready var stored = OS.get_window_size();
export var boundry = [Vector2(0,0), Vector2(1920*4,1080*2)];

func _input(event):
	#rewrite to C++/gdnative as a gdnative singleton (read up how to do that)
	if event.is_class("InputEventKey"):
		if event.is_pressed():
			#set_process_input(false);
			if event.scancode == KEY_F11:
				OS.set_window_fullscreen(!OS.window_fullscreen);
				if !OS.window_fullscreen:
					OS.set_window_size(stored);
				#set_process_input(true);
	#elif event.is_class("InputEventMouseButton"):
		#print("epic", event.get_button_index());
		
		
	pass;

	

func _ready():
	
	var a = RayCast2D;
	var b = a.new();
	
	#var c = b.instance();

	pass
