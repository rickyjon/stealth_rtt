#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

#include <Godot.hpp>
#include <Camera2D.hpp>
#include <Variant.hpp>
#include <InputEvent.hpp>
#include <Vector2.hpp>

namespace godot {

class CameraMovement : public godot::GodotScript<Camera2D> {
	GODOT_CLASS(CameraMovement)

public:
	static void _register_methods();

	int camera_speed;
	float time_passed;
	Vector2 viewport_size; //screen_size
	Vector2 viewport_leeway;
	Vector2 process_direction;
	*Unit selected_unit[];
	char no_selected_unit;
	CameraMovement();
	~CameraMovement();
	//void _init();

	void _process(float delta);
	void _input(Variant event);
	void _ready();

	float get_time_passed();

};

}

#endif
