#ifndef AIMBONE
#define AIMBONE

class CAimbone
{
public:
	void Draw();
	void CalculateHitbox( cl_entity_s *pEnt );
};

extern CAimbone Aimbone;

#endif