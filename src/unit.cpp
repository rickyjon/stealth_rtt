#include "unit.h"
#include <Label.hpp>
#include <InputEventMouse.hpp>
#include <InputEventMouseButton.hpp>

#include <CoreTypes.hpp>
#include <InputMap.hpp>
#include <Sprite.hpp>
#include <Camera2D.hpp>
#include <Viewport.hpp>
#include <SceneTree.hpp>
#include <AStar.hpp>
#include <Color.hpp>

using namespace godot;

void Unit::_register_methods() {

	register_method((char *)"_process", &Unit::_process);
	register_method((char *)"_ready", &Unit::_ready);
	register_method((char *)"_input", &Unit::_input);
	register_method((char *)"_draw", &Unit::_draw);
	//register_method((char *)"_find_path", &Unit::find_path);
	//register_property((char *)"base/name", &Unit::_name, String("Unit"));
	register_method((char *)"get_move_cursor_position", &Unit::get_move_cursor_position);
	//register_method((char *)"area_entered", &Unit::area_entered);
	register_property((char *)"selected", &Unit::selected, false);
}

Unit::Unit() {}

Unit::~Unit() {}

void Unit::_process(float delta) {

	move_to(delta, point_b);

}

void Unit::_ready() {

	point_b = owner->get_global_position();
	owner->set_process_input(false);
	owner->set("selected", false);
	Error e = owner->connect("area_entered", (Object *)this, "area_entered");

	if (e == Error::OK) {

		Godot::print("OK");

	}
	//selected = false;
	//selected = !selected;
	//owner->set_process(true);

}

void Unit::_input(Variant event) {

	InputEvent *ie = (InputEvent *)(Object *)event;

	//Godot::print(owner->get_parent()->get_name()
	//		+" IS SELECTED: "+String::num(selected));

	if (ie->get_class() == "InputEventMouseButton") {
		//Array a = owner->get_tree()->get_nodes_in_group("unit_squad");
		//Unit *u = (Unit *)(Object *)a[0];
		//int index = a.find((Variant *)(Object *)this);

/*
		Godot::print(owner->get_parent()->get_name()
			+ owner->get("selected")
			+" IS SELECTED: "+String::num(selected)
			//+String::num(index)
			);//+", OPEN_ARRAY SIZE:"+open_arr.size());
			/**/
		//if (index != -1) {
			//Unit *u = (Unit *)(Object *)a[index];
		if (owner->get("selected")) {
				//if (iemb->get_button_index() == 2) {
				//InputEventMouseButton *iemb = (InputEventMouseButton *)ie;
				//Godot::print(iemb->get_button_index());

			//get_move_cursor_position_a(ie);
				//}
		}
	}

}

void Unit::_draw() {

	//get transform -> get scale
	Color c = Color();
	Vector2 pa = owner->get_global_position();
	//Vector2 pr = owner->get_size()-owner->get_global_position();
	Vector2 pb = ((Node2D *)owner->get_parent()->get_node("MoveCursor"))
		->get_global_position();
	//owner->get_local_mouse_position()
	//owner->draw_line(Vector2(0, 0), pb-pa, c, 2.0, false);
	//get this to work later

}

void Unit::area_entered(Variant area) {

	//InputEventMouseButton *iemb = (InputEventMouseButton *)ie;
	Godot::print("area enterered");

}

void Unit::get_move_cursor_position() {

	Vector2 target = owner->get_global_mouse_position();
	point_b = target;
	owner->set_process(true);

}

void Unit::move_to(float delta, Vector2 point_b) {

	//Sprite *s = (Sprite *)owner->get_node("Sprite");
	Sprite *s = (Sprite *)owner->get_parent()->get_node("MoveCursor");
	Label *a = (Label *)owner->get_node("Label");

	Vector2 pos = owner->get_position();
	const int leeway = 20;
	float deg = pos.angle_to_point(point_b)*180/3.141; //angle to degrees
	Vector2 deg_vec = Vector2(cos(-deg), -sin(-deg));
	Vector2 movement_speed = Vector2(200, 200);
	Vector2 del = Vector2(delta, delta);
	Vector2 spd = (pos+(deg_vec*movement_speed*del));

	s->set_position(point_b);

	//leeway
	bool flag_x = (pos.x > point_b.x-leeway && pos.x < point_b.x+leeway);
	bool flag_y = (pos.y > point_b.y-leeway && pos.y < point_b.y+leeway);

	if (flag_x && flag_y) {
		owner->set_process(false);
	} else {
		owner->set_position(spd);
		owner->look_at(point_b);
		owner->update();
	}

}
/* move this to another file */
int Unit::astar_calculate_point_index(Vector2 *point, Vector2 *map_boundry) {
	return point->x + (map_boundry->x * point->y);
}

void Unit::astar_add_walk_cells(AStar *as) {

	Array map_boundries = owner->get_tree()->get_root()
		->get_node("Map")->get("Boundry");

	Array point_array = Array(); 
	Array obstacle_array = Array(); 

	int id = 0;
	Vector2 *map_boundry_nw = ((Vector2 *)(Object *)map_boundries[0]);
	Vector2 *map_boundry = ((Vector2 *)(Object *)map_boundries[1]);

	int x = 0; //use map_boundry_nw
	int y = 0;
	int map_end_x = (int)map_boundry->x;
	int map_end_y = (int)map_boundry->y;
	int point_index = 0;
		
	while(y < map_end_y) {
		while(x < map_end_y) {
			Vector2 point = Vector2(x, y);
			if (obstacle_array.has(point)) {
				continue;
			}
			point_array.append(point);
			
			point_index = astar_calculate_point_index((Vector2 *)&point,
				   	map_boundry);
			as->add_point(point_index, Vector3(x,y,0));
			++x;
		}
		++y;
	}
}

Array Unit::astar_con_walk_cells(AStar *as,  Array point_array) {

	Array map_boundries = owner->get_tree()->get_root()
		->get_node("Map")->get("Boundry");
	Vector2 *map_boundry = ((Vector2 *)(Object *)map_boundries[1]);

	int x = 0; //use map_boundry_nw
	int y = 0;
	int localx = -1; //use map_boundry_nw
	int localy = -1;
	const int LOCALMAX = 1;
	int index = 0;
	int length = point_array.size();

	while(index < length) {
		Vector2 *point = (Vector2 *)(Object *)point_array[index];
		int point_index = astar_calculate_point_index(point, map_boundry);
		localx = -1;
		localy = -1;
		while(localy <= LOCALMAX) {
			while(localx <= LOCALMAX) {
				/*
				Vector2 point = Vector2(x, y);
				if (obstacle_array.has(point)) {
					continue;
				}
				point_array.append(point);
				
				point_index = astar_calculate_point_index(point, map_boundry);
				as->add_point(point_index, Vector3(x,y,0));
				*/
				++localx;
			}
			++localy;
		}
		++index;
	}
	return point_array;
}

void Unit::get_points(AStar *as) {

	Array points = owner->get_tree()->get_root()
		->get_node("Map")->get("Boundry");
	//points.clear();
	int i = 0;
	int k = 0;
	int id = 0;
	int l = ((Vector2 *)(Object *)points[1])->x;
	int p = ((Vector2 *)(Object *)points[1])->y;
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

	i = 0;
	k = 0;
	while(i < l) {

		Vector2 v = (Vector2)points[i];
		as->add_point(id, vec_vec(v));
		//x
		/*
		while(k < p) {
			points.append(Vector2(i, k));
			++k;
		}
		*/
		++i;
		++id;
	}

	i = 0;
	int x = -1; int y = -1;
	const int z = 1;
	//connect to whatever

	while(i < id) {

		while(x < z) {
			while(y < z) {
				as->connect_points(id+x, id+y);
				++y;
			}
			++x;
		}
		++i;
	}


}

void Unit::find_path() {
//make every level have a set boundary
	AStar *as = new AStar();

	int i = 0;
	int l = 0;
	get_points((AStar *)as);

	//l = points.size();
/*
	while(i < l) {
		as->add_point(i, vec_vec((Vector2 *)(Object *)points[i]));
		++i;
	}
	* */
	//as->add_point(1, vec_vec(owner->get_position()));
	//as->add_point(2, vec_vec(point_b));

	//as->connect_points(1, 2, false);

	//PoolVector3Array pv3a = as->get_point_path(1, 2);
	//Godot::print(as->get_point_path(1, 2));

}

//void Unit::get_doors

//void Unit::get_walls

Vector3 Unit::vec_vec(Vector2 *a) {

	return Vector3(a->x, a->y, 0);

}

Vector3 Unit::vec_vec(Vector2 a) {

	return Vector3(a.x, a.y, 0);
}

Vector2 Unit::vec_vec(Vector3 a) {

	return Vector2(a.x, a.y);

}

Vector2 Unit::vec_vec(Vector3 *a) {

	return Vector2(a->x, a->y);

}

void Unit::action_1() {};
void Unit::action_2() {};
void Unit::action_3() {};
void Unit::action_4() {};
//void action_5() {};
//void action_6() {};
