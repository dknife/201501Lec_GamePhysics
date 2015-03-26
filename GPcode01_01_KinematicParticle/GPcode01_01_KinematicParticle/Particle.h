#ifndef _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_
#define _TONGMYONG_YMKANG_KINEMATIC_PARTICLE_2015_

class CParticle {

public:
	CParticle();

	void setPosition(double x, double y, double z);
	void setRadius(double r);

	void drawWithGL(void);
};

#endif