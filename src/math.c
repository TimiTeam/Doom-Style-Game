#include "main_head.h"

int			box_intersection(t_vector p1, t_vector p2, t_vector p3, t_vector p4)
{
	if ((Overlap(p1.x, p2.x, p3.x, p4.x) && Overlap(p1.y, p2.y, p3.y, p4.y)))
		return (1);
	return (0);
}

float			side_of_a_point(t_vector p, t_vector s, t_vector end)
{
	return (vxs((end.x)-(s.x), (end.y)-(s.y), (p.x)-(s.x), (p.y)-(s.y)));
}

t_vector	point_of_intersec(t_vector p1, t_vector p2, t_vector p3, t_vector p4)
{
	return ((t_vector){
	vxs(vxs(p1.x, p1.y, p2.x, p2.y), (p1.x)-(p2.x),
	vxs(p3.x, p3.x, p4.x, p4.y), (p3.x)-(p4.x))
	/ vxs((p1.x)-(p2.x), (p1.y)-(p2.y), (p3.x)-(p4.x), (p3.y)-(p4.y)),
	vxs(vxs(p1.x, p1.y, p2.x, p2.y), (p1.y)-(p2.y),
	vxs(p3.x, p3.y, p4.x, p4.y), (p3.y)-(p4.y))
	/ vxs((p1.x)-(p2.x), (p1.y)-(p2.y), (p3.x)-(p4.x), (p3.y)-(p4.y))
	});
}

t_scaler	init_scaler(int n, t_point curr, t_point dst)
{
    return ((t_scaler){ dst.x + (n-1 - curr.x) * (dst.y-dst.x) / (curr.y-curr.x), ((dst.y<dst.x) ^ (curr.y<curr.x)) ? -1 : 1,
      abs(dst.y-dst.x), abs(curr.y-curr.x), (int)((n-1-curr.x) * abs((int)(dst.y-dst.x))) % abs(curr.y-curr.x) });
}