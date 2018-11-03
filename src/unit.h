#ifndef UNIT_H
#define UNIT_H

#include <Godot.hpp>
#include <Area2D.hpp>
#include <String.hpp>
#include <Variant.hpp>
#include <Vector2.hpp>
#include <Array.hpp>

namespace godot {

struct area {

	area *parent;
	int f_cost;
	int h_cost;
	int g_cost;
	bool traversable;

};

class Unit : public godot::GodotScript<Area2D> {
	GODOT_CLASS(Unit)

public:
	Array open_arr;
	Array closed_arr;
	static void _register_methods();

	float time_passed;
	Vector2 point_b;
	Unit();
	~Unit();

	void _process(float delta);
	void _input(Variant event);
	void find_path();
	String _name;

};

}

#endif
