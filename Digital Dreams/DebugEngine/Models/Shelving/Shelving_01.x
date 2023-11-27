xof 0303txt 0032
template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}


Frame {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame Box07 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.439552,29.159117,-20.218056,1.000000;;
  }

  Mesh  {
   24;
   -40.381987;0.000000;-0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;0.000000;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;;
   12;
   3;2,3,0;,
   3;1,0,3;,
   3;5,7,4;,
   3;6,4,7;,
   3;20,8,21;,
   3;9,21,8;,
   3;10,11,12;,
   3;13,12,11;,
   3;14,22,15;,
   3;23,15,22;,
   3;16,17,18;,
   3;19,18,17;;

   MeshNormals {
    24;
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;2,3,0;,
    3;1,0,3;,
    3;5,7,4;,
    3;6,4,7;,
    3;20,8,21;,
    3;9,21,8;,
    3;10,11,12;,
    3;13,12,11;,
    3;14,22,15;,
    3;23,15,22;,
    3;16,17,18;,
    3;19,18,17;;
   }

   MeshTextureCoords {
    24;
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_02.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    5,
    4,
    3,
    7,
    1,
    5,
    2,
    3,
    0,
    4,
    2,
    6,
    1,
    0,
    6,
    7;
   }
  }
 }

 Frame Box03 {
  

  FrameTransformMatrix {
   0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,39.208282,0.000000,-19.487629,1.000000;;
  }

  Mesh  {
   24;
   -5.012059;0.000000;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;614.94003;-4.978193;,
   -5.012059;614.94003;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;4.978193;;
   12;
   3;0,3,2;,
   3;3,0,1;,
   3;4,7,5;,
   3;7,4,6;,
   3;8,9,10;,
   3;9,8,11;,
   3;20,21,12;,
   3;21,20,13;,
   3;14,15,16;,
   3;15,14,17;,
   3;18,19,22;,
   3;19,18,23;;

   MeshNormals {
    24;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;;
    12;
    3;0,3,2;,
    3;3,0,1;,
    3;4,7,5;,
    3;7,4,6;,
    3;8,9,10;,
    3;9,8,11;,
    3;20,21,12;,
    3;21,20,13;,
    3;14,15,16;,
    3;15,14,17;,
    3;18,19,22;,
    3;19,18,23;;
   }

   MeshTextureCoords {
    24;
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_01.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    5,
    1,
    4,
    3,
    5,
    3,
    6,
    2,
    7,
    2,
    4,
    1,
    7,
    0,
    6;
   }
  }
 }

 Frame Box04 {
  

  FrameTransformMatrix {
   0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,39.206605,0.000000,19.098987,1.000000;;
  }

  Mesh  {
   24;
   -5.012059;0.000000;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;614.94003;-4.978193;,
   -5.012059;614.94003;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;4.978193;;
   12;
   3;0,3,2;,
   3;3,0,1;,
   3;4,7,5;,
   3;7,4,6;,
   3;8,9,10;,
   3;9,8,11;,
   3;20,21,12;,
   3;21,20,13;,
   3;14,15,16;,
   3;15,14,17;,
   3;18,19,22;,
   3;19,18,23;;

   MeshNormals {
    24;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;;
    12;
    3;0,3,2;,
    3;3,0,1;,
    3;4,7,5;,
    3;7,4,6;,
    3;8,9,10;,
    3;9,8,11;,
    3;20,21,12;,
    3;21,20,13;,
    3;14,15,16;,
    3;15,14,17;,
    3;18,19,22;,
    3;19,18,23;;
   }

   MeshTextureCoords {
    24;
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_01.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    5,
    1,
    4,
    3,
    5,
    3,
    6,
    2,
    7,
    2,
    4,
    1,
    7,
    0,
    6;
   }
  }
 }

 Frame Box05 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.439552,89.750810,-20.218059,1.000000;;
  }

  Mesh  {
   24;
   -40.381987;0.000000;-0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;0.000000;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;;
   12;
   3;2,3,0;,
   3;1,0,3;,
   3;5,7,4;,
   3;6,4,7;,
   3;20,8,21;,
   3;9,21,8;,
   3;10,11,12;,
   3;13,12,11;,
   3;14,22,15;,
   3;23,15,22;,
   3;16,17,18;,
   3;19,18,17;;

   MeshNormals {
    24;
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;2,3,0;,
    3;1,0,3;,
    3;5,7,4;,
    3;6,4,7;,
    3;20,8,21;,
    3;9,21,8;,
    3;10,11,12;,
    3;13,12,11;,
    3;14,22,15;,
    3;23,15,22;,
    3;16,17,18;,
    3;19,18,17;;
   }

   MeshTextureCoords {
    24;
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_02.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    5,
    4,
    3,
    7,
    1,
    5,
    2,
    3,
    0,
    4,
    2,
    6,
    1,
    0,
    6,
    7;
   }
  }
 }

 Frame Box06 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,-0.439552,60.182848,-20.218056,1.000000;;
  }

  Mesh  {
   24;
   -40.381987;0.000000;-0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   40.381987;0.000000;0.677983;,
   40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   40.381987;0.000000;0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;-0.677983;,
   -40.381987;0.000000;0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;0.000000;-0.677983;,
   -40.381987;0.000000;-0.677983;,
   -40.381987;-40.062224;0.677983;,
   40.381987;-40.062224;0.677983;;
   12;
   3;2,3,0;,
   3;1,0,3;,
   3;5,7,4;,
   3;6,4,7;,
   3;20,8,21;,
   3;9,21,8;,
   3;10,11,12;,
   3;13,12,11;,
   3;14,22,15;,
   3;23,15,22;,
   3;16,17,18;,
   3;19,18,17;;

   MeshNormals {
    24;
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;;
    12;
    3;2,3,0;,
    3;1,0,3;,
    3;5,7,4;,
    3;6,4,7;,
    3;20,8,21;,
    3;9,21,8;,
    3;10,11,12;,
    3;13,12,11;,
    3;14,22,15;,
    3;23,15,22;,
    3;16,17,18;,
    3;19,18,17;;
   }

   MeshTextureCoords {
    24;
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_02.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    5,
    4,
    3,
    7,
    1,
    5,
    2,
    3,
    0,
    4,
    2,
    6,
    1,
    0,
    6,
    7;
   }
  }
 }

 Frame Box01 {
  

  FrameTransformMatrix {
   0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,-40.079437,0.000000,19.116986,1.000000;;
  }

  Mesh  {
   24;
   -5.012059;0.000000;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;614.94003;-4.978193;,
   -5.012059;614.94003;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;4.978193;;
   12;
   3;0,3,2;,
   3;3,0,1;,
   3;4,7,5;,
   3;7,4,6;,
   3;8,9,10;,
   3;9,8,11;,
   3;20,21,12;,
   3;21,20,13;,
   3;14,15,16;,
   3;15,14,17;,
   3;18,19,22;,
   3;19,18,23;;

   MeshNormals {
    24;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;;
    12;
    3;0,3,2;,
    3;3,0,1;,
    3;4,7,5;,
    3;7,4,6;,
    3;8,9,10;,
    3;9,8,11;,
    3;20,21,12;,
    3;21,20,13;,
    3;14,15,16;,
    3;15,14,17;,
    3;18,19,22;,
    3;19,18,23;;
   }

   MeshTextureCoords {
    24;
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_01.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    5,
    1,
    4,
    3,
    5,
    3,
    6,
    2,
    7,
    2,
    4,
    1,
    7,
    0,
    6;
   }
  }
 }

 Frame Box02 {
  

  FrameTransformMatrix {
   0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,0.000000,0.000000,0.000000,0.146882,0.000000,-40.091872,0.000000,-19.483371,1.000000;;
  }

  Mesh  {
   24;
   -5.012059;0.000000;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;614.94003;-4.978193;,
   -5.012059;614.94003;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   5.012059;614.94003;-4.978193;,
   5.012059;0.000000;4.978193;,
   -5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;4.978193;,
   -5.012059;614.94003;-4.978193;,
   5.012059;0.000000;-4.978193;,
   5.012059;614.94003;4.978193;,
   -5.012059;0.000000;-4.978193;,
   -5.012059;614.94003;4.978193;;
   12;
   3;0,3,2;,
   3;3,0,1;,
   3;4,7,5;,
   3;7,4,6;,
   3;8,9,10;,
   3;9,8,11;,
   3;20,21,12;,
   3;21,20,13;,
   3;14,15,16;,
   3;15,14,17;,
   3;18,19,22;,
   3;19,18,23;;

   MeshNormals {
    24;
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;-1.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;0.000000;1.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;,
    -1.000000;0.000000;0.000000;;
    12;
    3;0,3,2;,
    3;3,0,1;,
    3;4,7,5;,
    3;7,4,6;,
    3;8,9,10;,
    3;9,8,11;,
    3;20,21,12;,
    3;21,20,13;,
    3;14,15,16;,
    3;15,14,17;,
    3;18,19,22;,
    3;19,18,23;;
   }

   MeshTextureCoords {
    24;
    1.000000;1.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    0.000000;1.000000;,
    1.000000;0.000000;,
    1.000000;1.000000;,
    0.000000;0.000000;;
   }

   MeshMaterialList {
    1;
    12;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material {
     1.000000;1.000000;1.000000;1.000000;;
     3.200000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "\Models\\\\Shelving\\\\shelving_01.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    24;
    8;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    0,
    5,
    1,
    4,
    3,
    5,
    3,
    6,
    2,
    7,
    2,
    4,
    1,
    7,
    0,
    6;
   }
  }
 }
}