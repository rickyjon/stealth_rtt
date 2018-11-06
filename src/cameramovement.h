#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

#include <Godot.hpp>
#include <Camera2D.hpp>
#include <Variant.hpp>
#include <InputEvent.hpp>
#include <Vector2.hpp>

#include "unit.h"

namespace godot {

class CameraMovement : public godot::GodotScript<Camera2D> {
	GODOT_CLASS(CameraMovement)

public:
	static void _register_methods();

	int camera_speed;
	Vector2 viewport_size; //screen_size
	Vector2 viewport_leeway;
	Vector2 process_direction;
	CameraMovement();
	~CameraMovement();

	void _process(float delta);
	void _input(Variant event);
	void _ready();

	//functions
	void directional_edge(InputEvent *ie);
	void move_camera_unit(int i);
	void center_camera();
	//flexible array member
	char no_selected_unit;
	Unit *selected_unit[];

};

}

#endif
