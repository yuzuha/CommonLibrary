xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 120;
 -5.00000;25.00000;-5.00000;,
 5.00000;25.00000;-5.00000;,
 5.00000;15.00000;-5.00000;,
 -5.00000;15.00000;-5.00000;,
 5.00000;25.00000;-5.00000;,
 5.00000;25.00000;5.00000;,
 5.00000;15.00000;5.00000;,
 5.00000;15.00000;-5.00000;,
 5.00000;25.00000;5.00000;,
 -5.00000;25.00000;5.00000;,
 -5.00000;15.00000;5.00000;,
 5.00000;15.00000;5.00000;,
 -5.00000;25.00000;5.00000;,
 -5.00000;25.00000;-5.00000;,
 -5.00000;15.00000;-5.00000;,
 -5.00000;15.00000;5.00000;,
 5.00000;25.00000;-5.00000;,
 -5.00000;25.00000;-5.00000;,
 -5.00000;15.00000;-5.00000;,
 5.00000;15.00000;-5.00000;,
 -3.75000;15.00000;-2.50000;,
 3.75000;15.00000;-2.50000;,
 3.75000;6.00000;-2.50000;,
 -3.75000;6.00000;-2.50000;,
 3.75000;15.00000;-2.50000;,
 3.75000;15.00000;2.50000;,
 3.75000;6.00000;2.50000;,
 3.75000;6.00000;-2.50000;,
 3.75000;15.00000;2.50000;,
 -3.75000;15.00000;2.50000;,
 -3.75000;6.00000;2.50000;,
 3.75000;6.00000;2.50000;,
 -3.75000;15.00000;2.50000;,
 -3.75000;15.00000;-2.50000;,
 -3.75000;6.00000;-2.50000;,
 -3.75000;6.00000;2.50000;,
 3.75000;15.00000;-2.50000;,
 -3.75000;15.00000;-2.50000;,
 -3.75000;6.00000;-2.50000;,
 3.75000;6.00000;-2.50000;,
 0.75000;6.00000;-2.00000;,
 3.25000;6.00000;-2.00000;,
 3.25000;-0.00000;-2.00000;,
 0.75000;-0.00000;-2.00000;,
 3.25000;6.00000;-2.00000;,
 3.25000;6.00000;2.00000;,
 3.25000;-0.00000;2.00000;,
 3.25000;-0.00000;-2.00000;,
 3.25000;6.00000;2.00000;,
 0.75000;6.00000;2.00000;,
 0.75000;-0.00000;2.00000;,
 3.25000;-0.00000;2.00000;,
 0.75000;6.00000;2.00000;,
 0.75000;6.00000;-2.00000;,
 0.75000;-0.00000;-2.00000;,
 0.75000;-0.00000;2.00000;,
 3.25000;6.00000;-2.00000;,
 0.75000;6.00000;-2.00000;,
 0.75000;-0.00000;-2.00000;,
 3.25000;-0.00000;-2.00000;,
 -3.25000;6.00000;-2.00000;,
 -0.75000;6.00000;-2.00000;,
 -0.75000;-0.00000;-2.00000;,
 -3.25000;-0.00000;-2.00000;,
 -0.75000;6.00000;-2.00000;,
 -0.75000;6.00000;2.00000;,
 -0.75000;-0.00000;2.00000;,
 -0.75000;-0.00000;-2.00000;,
 -0.75000;6.00000;2.00000;,
 -3.25000;6.00000;2.00000;,
 -3.25000;-0.00000;2.00000;,
 -0.75000;-0.00000;2.00000;,
 -3.25000;6.00000;2.00000;,
 -3.25000;6.00000;-2.00000;,
 -3.25000;-0.00000;-2.00000;,
 -3.25000;-0.00000;2.00000;,
 -0.75000;6.00000;-2.00000;,
 -3.25000;6.00000;-2.00000;,
 -3.25000;-0.00000;-2.00000;,
 -0.75000;-0.00000;-2.00000;,
 3.75000;15.00000;-2.00000;,
 6.25000;15.00000;-2.00000;,
 6.25000;5.00000;-2.00000;,
 3.75000;5.00000;-2.00000;,
 6.25000;15.00000;-2.00000;,
 6.25000;15.00000;2.00000;,
 6.25000;5.00000;2.00000;,
 6.25000;5.00000;-2.00000;,
 6.25000;15.00000;2.00000;,
 3.75000;15.00000;2.00000;,
 3.75000;5.00000;2.00000;,
 6.25000;5.00000;2.00000;,
 3.75000;15.00000;2.00000;,
 3.75000;15.00000;-2.00000;,
 3.75000;5.00000;-2.00000;,
 3.75000;5.00000;2.00000;,
 6.25000;15.00000;-2.00000;,
 3.75000;15.00000;-2.00000;,
 3.75000;5.00000;-2.00000;,
 6.25000;5.00000;-2.00000;,
 -6.25000;15.00000;-2.00000;,
 -3.75000;15.00000;-2.00000;,
 -3.75000;5.00000;-2.00000;,
 -6.25000;5.00000;-2.00000;,
 -3.75000;15.00000;-2.00000;,
 -3.75000;15.00000;2.00000;,
 -3.75000;5.00000;2.00000;,
 -3.75000;5.00000;-2.00000;,
 -3.75000;15.00000;2.00000;,
 -6.25000;15.00000;2.00000;,
 -6.25000;5.00000;2.00000;,
 -3.75000;5.00000;2.00000;,
 -6.25000;15.00000;2.00000;,
 -6.25000;15.00000;-2.00000;,
 -6.25000;5.00000;-2.00000;,
 -6.25000;5.00000;2.00000;,
 -3.75000;15.00000;-2.00000;,
 -6.25000;15.00000;-2.00000;,
 -6.25000;5.00000;-2.00000;,
 -3.75000;5.00000;-2.00000;;
 
 36;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;;
 
 MeshMaterialList {
  1;
  36;
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
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "../Resource/Game/Player/Model_Player_Texture1.bmp";
   }
  }
 }
 MeshNormals {
  24;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  36;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;;
 }
 MeshTextureCoords {
  120;
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.950000;0.450000;,
  0.550000;0.450000;,
  0.550000;0.050000;,
  0.950000;0.050000;;
 }
 MeshVertexColors {
  120;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;;
 }
}
