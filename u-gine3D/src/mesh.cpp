#include "../include/mesh.h"
#include "../lib/rapidjson/document.h"
#include "../include/resourcemanager.h"

using namespace rapidjson;

Ptr<Mesh> Mesh::Create()
{
  return new Mesh();
}

Ptr<Mesh> Mesh::Create(const String& filename)
{
  String read = String::Read(filename);
  if (read == "") return nullptr;

  Document document;
  document.Parse<0>(read.ToCString());
  if (document.HasParseError()) return nullptr;
  if (!document.IsObject()) return nullptr;
  if (!document.HasMember("submeshes")) return nullptr;
  if (!document["submeshes"].IsArray()) return nullptr;
  SizeType size = document["submeshes"].Size();
  const Value& submeshes = document["submeshes"];

  Mesh *mesh = new Mesh();
  for (SizeType i = 0; i < size; i++)
  {
    if (submeshes[i].IsObject())
    {
      Ptr<Submesh> submesh = Submesh::Create();
      if (submeshes[i].HasMember("texture")){
        String strTexture = submeshes[i]["texture"].GetString();
        String dir = filename.ExtractDir();
        if (dir != ""){
          String ruta = "/";
          strTexture = dir + ruta + strTexture;
        }
        Ptr<Texture> tex = Texture::Create(strTexture);
        submesh->SetTexture(tex);
      }

      if (submeshes[i].HasMember("color"))
        if (submeshes[i]["color"].IsArray()){
          int indice = 0;
          vec3 colour(submeshes[i]["color"][indice].GetDouble(), submeshes[i]["color"][indice + 1].GetDouble(), submeshes[i]["color"][indice + 2].GetDouble());
          submesh->SetColor(colour);
        }
      
      if (submeshes[i].HasMember("shininess")) {
        submesh->SetShininess(submeshes[i]["shininess"].GetInt());
      }

      if (submeshes[i].HasMember("indices"))
        if (submeshes[i]["indices"].IsArray()){
          const Value& indices = submeshes[i]["indices"];
          SizeType numInd = indices.Size();
          for (SizeType j = 0; j < numInd; j += 3)
            submesh->AddTriangle(indices[j].GetInt(), indices[j + 1].GetInt(), indices[j + 2].GetInt());
        }

      if (submeshes[i].HasMember("coords"))
        if (submeshes[i]["coords"].IsArray()){ 
          
          SizeType numCoords = submeshes[i]["coords"].Size();
          SizeType numTexCoords = 0;
          SizeType numNormals = 0;

          if (submeshes[i].HasMember("texcoords"))
            if (submeshes[i]["texcoords"].IsArray())
              numTexCoords = submeshes[i]["texcoords"].Size();

          if (submeshes[i].HasMember("normals"))
            if (submeshes[i]["normals"].IsArray())
              numNormals = submeshes[i]["normals"].Size();

          for (SizeType j = 0, z = 0; j < numCoords; j += 3, z+=2)
          {
            vec3 coord = vec3(0,0,0);
            vec3 normals = vec3(0, 0, 0);
            vec2 texcoord = vec2(0, 0);

            coord.x = submeshes[i]["coords"][j].GetDouble();
            coord.y = submeshes[i]["coords"][j + 1].GetDouble();
            coord.z = submeshes[i]["coords"][j + 2].GetDouble();

            if (j < numNormals) {
              normals.x = submeshes[i]["normals"][j].GetDouble();
              normals.y = submeshes[i]["normals"][j + 1].GetDouble();
              normals.z = submeshes[i]["normals"][j + 2].GetDouble();
            }

            if (z < numTexCoords) {
              texcoord.x = submeshes[i]["texcoords"][z].GetDouble();
              texcoord.y = submeshes[i]["texcoords"][z + 1].GetDouble();
            }

            Vertex vertice(coord, texcoord, normals);
            submesh->AddVertex(vertice);
          }
         
        }
      mesh->AddSubmesh(submesh);
    }
  }
  mesh->mFilename = filename;
  return mesh;
}

void Mesh::Render()
{
  uint32 numSubMeshes = mSubmeshes.Size();
  for (uint32 i = 0; i < numSubMeshes; i++)
    mSubmeshes[i]->Render();
}