#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <String.hpp>
#include <Variant.hpp>
#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Array.hpp>
#include <InputEvent.hpp>
#include <InputEventMouseButton.hpp>

namespace godot {
/*
struct area {
	area *parent;
	int f_cost;
	int h_cost;
	int g_cost;
	bool traversable;
};
*/
class Unit : public godot::GodotScript<Area2D> {
	GODOT_CLASS(Unit)
private:

	Vector3 vec_vec(Vector2 a);
	Vector2 vec_vec(Vector3 a);
	Vector3 vec_vec(Vector2 *a);
	Vector2 vec_vec(Vector3 *a);

public:
	static void _register_methods();

	//complex data
	Array open_arr = Array();
	Array closed_arr;
	Vector2 point_b;

	//simple data
	bool selected;

	Unit();
	~Unit();

	void _process(float delta);
	void _ready();
	void _input(Variant event);
	void _draw();

	//functions
	void move_camera_unit(int i);
	void move_to(float delta, Vector2 point_b);
	void find_path();
	void get_move_cursor_position_a(InputEventMouseButton *iemb);
	void get_move_cursor_position(Vector2 v);

	//virtual

	virtual void action_1();
	virtual void action_2();
	virtual void action_3();
	virtual void action_4();
	/*
	virtual void action_5();
	*/
	//virtual void action_6() = 0;

	//returning functions
	Array get_points();

};
}
#endif
