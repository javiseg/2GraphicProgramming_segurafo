#pragma once


class EffectCreator
{
public:
	EffectCreator();
	~EffectCreator();

	void RingOfCubes(int ring);
	void set_ring_done(bool srd);
	bool isRingDone();
	int numberCubes();

	void MoveOutRings();
	void DestroyRings();

	void sphereWave();


private:

	bool ring_done_;
	int num_cubes_;
	const int num_spheres_ = 104;
};

