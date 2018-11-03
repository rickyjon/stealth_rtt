#include "unit.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>

#include <InputMap.hpp>
#include <Object.hpp>
#include <Sprite.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>
#include <AStar.hpp>
#include <Label.hpp>

using namespace godot;

void Unit::_register_methods() {

	register_method((char *)"_process", &Unit::_process);
	register_method((char *)"_ready", &Unit::_ready);
	register_method((char *)"_input", &Unit::_input);
	//register_method((char *)"_find_path", &Unit::find_path);
	//register_property((char *)"base/name", &Unit::_name, String("Unit"));
}

Unit::Unit() {

}

Unit::~Unit() {
	// add your cleanup here
}

void Unit::_ready() {

	point_b = owner->get_global_position();
	owner->set_process(true);

}

void Unit::_process(float delta) {

	move_to(point_b);

}

void Unit::_input(Variant event) {

	InputEvent *ie = (InputEvent *)((Object *)event);

	if (ie->get_class() == "InputEventMouseButton") {

		get_move_cursor_position(ie);

	} else {
		if (ie->is_action("camera_center")) { //move this into cameramovement
			((Camera2D *)owner->get_parent()->get_parent()->get_node("Camera2D"))
				->set_position(owner->get_position());
		}
	}

}

void Unit::get_move_cursor_position(InputEvent *ie) {

	Vector2 a = ((Vector2)owner->get_viewport()->get("size"))/Vector2(2, 2);

	InputEventMouseButton *iemb = (InputEventMouseButton *)ie;
	if (iemb->get_button_index() == 1) {
		Vector2 target;
		target = iemb->get_global_position()-a;

		Camera2D *c = (Camera2D *)owner->get_parent()->get_parent()
			->get_node("Camera2D");
		target = c->get_global_position()+target;

		point_b = target;

		owner->set_process(true);
	}

}

void Unit::move_to(Vector2 point_b) {

	//Sprite *s = (Sprite *)owner->get_node("Sprite");
	Sprite *s = (Sprite *)owner->get_parent()->get_node("MoveCursor");

	Label *a = (Label *)owner->get_node("Label");

	Vector2 pos = owner->get_position();
	const int leeway = 20;
	float deg = pos.angle_to_point(point_b)*180/3.141;
	Vector2 spd = (pos+Vector2(cos(-deg), -sin(-deg)));

	s->set_position(point_b);

	//s->set_global_position(point_b);
	//owner->set_position(point_b);

	bool flag_x = (pos.x > point_b.x-leeway && pos.x < point_b.x+leeway);
	bool flag_y = (pos.y > point_b.y-leeway && pos.y < point_b.y+leeway);

	//Godot::print(String::num(deg));
	//Godot::print(String::num(flag_x_1));
	//Godot::print(String::num(flag_x_2));
	//Godot::print(spd);
	//Godot::print(spd.floor());

	if (flag_x && flag_y) {
		owner->set_process(false);
	} else {
		owner->set_position(spd);
		owner->look_at(point_b);
	}

}

void Unit::find_path() {

	AStar *as = new AStar();

}

