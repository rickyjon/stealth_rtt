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

	Array open_arr;
	Array closed_arr;
	Vector2 point_b;
	bool selected;
	Unit();
	~Unit();

	void _ready();
	void _process(float delta);
	void _input(Variant event);

	void move_camera_unit(int i);
	void move_to(Vector2 point_b);
	void find_path();
	Array get_points();
	void get_move_cursor_position(InputEvent *ie);
	//String _name;
};
}
#endif
