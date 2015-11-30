#include "../Vertex.h"
static float planeCount = 6;
//glDrawArrays(GL_TRIANGLES, 0, pocetPrvku);;
static Vertex planeVertices[6] = {
	{ {  1.0f, 0.0f, 1.0f  }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
	{ {  1.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
	{ { -1.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },

	{ { -1.0f, 0.0f, 1.0f  }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
	{ {  1.0f, 0.0f, 1.0f  }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
	{ { -1.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } }
};
