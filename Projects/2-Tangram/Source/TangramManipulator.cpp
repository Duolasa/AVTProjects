#include "TangramManipulator.h"



TangramManipulator::TangramManipulator()
{
}

TangramManipulator::~TangramManipulator()
{

}

void TangramManipulator::fillVertexBuffer(GLuint VboId[]){

  const Vertex Vertices [] =
  {
    { { -0.525f, -0.525f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }},
    { { 0.525f, -0.525f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },

    { { 0.525f, -0.525f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } },
    { { 0.525f, 0.525f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } },
    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.8f, 0.0f, 0.2f, 1.0f } },

    { { 0.525f, 0.525f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } },
    { { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } },
    { { 0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.3f, 0.5f, 1.0f, 1.0f } },

    { { -0.525f, 0.525f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } },
    { { -0.525f, 0.0f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } },
    { { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.4f, 0.5f, 0.0f, 1.0f } },

    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.5f, 0.0f, 0.0f, 1.0f } },
    { { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.5f, 0.0f, 0.0f, 1.0f } },
    { { -0.2625f, -0.2625f, 0.0f, 1.0f }, { 0.5f, 0.0f, 0.0f, 1.0f } },

    { { 0.0f, 0.0f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } },
    { { 0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } },
    { { 0.0f, 0.525f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } },
    { { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.8f, 0.5f, 1.0f, 1.0f } },

    { { -0.525f, -0.525f, 0.0f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } },
    { { -0.525f, 0.0f, 0.0f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } },
    { { -0.2625f, 0.2625f, 0.0f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } },
    { { -0.2625f, -0.2625f, 0.0f, 1.0f }, { 0.3f, 0.3f, 0.3f, 1.0f } },
    
    { { -1.0f, -1.0f, 0.20f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
    { { -1.0f, 1.0f, 0.20f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
    { { 1.0f, 1.0f, 0.20f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } },
    { { 1.0f, -1.0f, 0.20f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }

  };

  const GLubyte Indices [] =
  {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    17, 18, 15,
    19, 21, 20,
    19, 22, 21,
    25, 24, 23, 
    25, 23, 26
  };

  glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(VERTICES);
  glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(COLORS);
  glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) sizeof(Vertices[0].XYZW));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

}
