#ifndef MOUSEMOVEMENT_H
#define MOUSEMOVEMENT_H

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

	float time_passed;
	Vector2 viewport_size; //screen_size
	Vector2 process_direction;
	CameraMovement();
	~CameraMovement();
	//void _init();

	void _process(float delta);
	void _input(Variant event);

	float get_time_passed();

};

}

#endif
