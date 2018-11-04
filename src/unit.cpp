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
#include <PoolArrays.hpp>

using namespace godot;

void Unit::_register_methods() {

	register_method((char *)"_process", &Unit::_process);
	register_method((char *)"_ready", &Unit::_ready);
	register_method((char *)"_input", &Unit::_input);
	//register_method((char *)"_find_path", &Unit::find_path);
	//register_property((char *)"base/name", &Unit::_name, String("Unit"));
}

Unit::Unit() {}

Unit::~Unit() {}

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
		if (ie->is_action("camera_center")) { 
			//TODO:move this into cameramovement
			((Camera2D *)owner->get_parent()->get_parent()
				->get_node("Camera2D"))
					->set_position(owner->get_position());
		} else if (ie->is_action("unit_1")) {
			move_camera_unit(1);	
			Godot::print("Pressed Key 1");
		} else if (ie->is_action("unit_2")) {
			move_camera_unit(2);	
		} else if (ie->is_action("unit_3")) {
			move_camera_unit(3);	
		} else if (ie->is_action("unit_4")) {
			move_camera_unit(4);	
		} //for the sake of this game, limit to 4 characters
		
	}

}

void Unit::move_camera_unit(int i) {

	Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
	
	int l = a.size();
	Camera2D *c = ((Camera2D *)owner->get_parent()->get_parent()
					->get_node("Camera2D"));
						//->set_position(owner->get_position());

	--i;
	if (i < l) {
		
		Node2D *n = (Node2D *)(Object *)a[i];
		Unit *u = (Unit *)(Object *)a[i];

		u->selected = true;
		//c->set_position(u->owner->get_position());
		c->set_position(n->get_position());
		//Godot::print(u->owner->get_position());
		//Godot::print(u->owner->get("name"));
			
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
	float deg = pos.angle_to_point(point_b)*180/3.141; //angle to degrees
	Vector2 spd = (pos+Vector2(cos(-deg), -sin(-deg)));

	s->set_position(point_b);

	//s->set_global_position(point_b);
	//owner->set_position(point_b);

	//leeway
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

Array Unit::get_points() {

	Array maximum = owner->get_tree()->get_root()
		->get_node("Map")->get("Boundry");
	Array points = maximum;
	points.clear();
	int i = 0;
	int k = 0;
	int l = ((Vector2 *)(Object *)maximum[0])->x;
	int p = ((Vector2 *)(Object *)maximum[0])->y;
	//y
	while(i < l) {
		points.append(Vector2(i, 0));
		//x
		while(k < p) {
			points.append(Vector2(i, k));
			++k;
		}
		++i;
	}

	return points;

}

void Unit::find_path() {
//make every level have a set boundary
	AStar *as = new AStar();

	int i = 0;
	int l = 0;
	Array points = get_points();
	l = points.size();

	while(i < l) {
		as->add_point(i, vec_vec((Vector2 *)(Object *)points[i]));
		++i;	
	}
	//as->add_point(1, vec_vec(owner->get_position()));
	//as->add_point(2, vec_vec(point_b));
	
	as->connect_points(1, 2, false);
	
	PoolVector3Array pv3a = as->get_point_path(1, 2);
	//Godot::print(as->get_point_path(1, 2));

}


Vector3 Unit::vec_vec(Vector2 *a) {

	return Vector3(a->x, a->y, 0);

}

Vector3 Unit::vec_vec(Vector2 a) {

	return Vector3(a.x, a.y, 0);
}

Vector2 Unit::vec_vec(Vector3 a) {

	return Vector2(a.x, a.y);

}
