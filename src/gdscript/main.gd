extends Node

# class member variables go here, for example:
# var a = 2
# var b = "textvar"

func _input(event):
	
	return;
	print(event.get_class());
	if (event.get_class() == "InputEventMouseMotion"):
		
		var speed = Vector2(100, 100);
		var pos =  event.get_position()
		var c = get_node("Camera2D");
		var c_pos = c.get_position();
		
		
		#speed *= bool(c_pos)
		
		if (c_pos < Vector2(100, 100) ||c_pos < Vector2(222, 222) ):
			c.set_global_position(c.get_position()+speed);
		
		get_node("Label").text = str(pos+speed);
		#InputEventMouseMotion.speed;
		print(1);
	
	pass;

func _ready():
	print(OS.get_name());
	set_process(true)
	pass

func _process(delta):

	pass
