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

  if (document.HasMember("sequences"))
    if (document["sequences"].IsArray()) {
      SizeType size = document["sequences"].Size();
      const Value& sequences = document["sequences"];
      for (SizeType i = 0; i < size; i++)
      {
        String name = "";
        int first = 0;
        int last = 0;
        if (sequences[i].IsObject())
        {
          if (sequences[i].HasMember("name"))
             name = submeshes[i]["name"].GetString();
          if (sequences[i].HasMember("first_frame"))
            first = submeshes[i]["first_frame"].GetUint();
          if (sequences[i].HasMember("last_frame"))
            last = submeshes[i]["last_frame"].GetUint();
          AnimSeq seq(name, first, last);
          mesh->AddSequence(seq);
        }
      }
    }

  if (document.HasMember("bones"))
    if (document["bones"].IsArray()) 
    {
      SizeType size = document["bones"].Size();
      const Value& bones = document["bones"];
      for (SizeType i = 0; i < size; i++)
      {
        String name = "";
        String parent = "";
        mat4 transform = glm::mat4();
        Array<uint32> submeshes;
        if (bones[i].IsObject())
        {
          if (bones[i].HasMember("name"))
            name = bones[i]["name"].GetString();
          if (bones[i].HasMember("parent"))
            parent = bones[i]["parent"].GetString();
          if (bones[i].HasMember("transform")) {
            SizeType transSize = bones[i]["transform"].Size();
            for (uint32 j = 0; j < transSize; j++)
              glm::value_ptr(transform)[j] = bones[i]["transform"][j].GetDouble();
          }
          if (bones[i].HasMember("submeshes")) {
            SizeType subSize = bones[i]["submeshes"].Size();
            for (uint32 j = 0; j < subSize; j++)
              submeshes.Add(bones[i]["submeshes"][j].GetUint());
          
          }
          Ptr<Bone> bone = Bone::Create(name, transform, submeshes);
          if (bones[i].HasMember("positions")) {
            SizeType posSize = bones[i]["positions"].Size();
            for (uint32 j = 0; j < posSize; j+=4) {
              vec3 position(0, 0, 0);
              uint32 keyFrame = bones[i]["positions"][j].GetUint();
              position.x = bones[i]["positions"][j + 1].GetDouble();
              position.y = bones[i]["positions"][j + 2].GetDouble();
              position.z = bones[i]["positions"][j + 3].GetDouble();
              bone->AddPosition(keyFrame, position);
            }
          }

          if (bones[i].HasMember("rotations")) {
            SizeType rotSize = bones[i]["rotations"].Size();
            for (uint32 j = 0; j < rotSize; j += 5) {
              quat rotation(1, 0, 0, 0);
              uint32 keyFrame = bones[i]["rotations"][j].GetUint();
              rotation.w = bones[i]["rotations"][j + 1].GetDouble();
              rotation.x = bones[i]["rotations"][j + 2].GetDouble();
              rotation.y = bones[i]["rotations"][j + 3].GetDouble();
              rotation.z = bones[i]["rotations"][j + 3].GetDouble();
              bone->AddRotation(keyFrame, rotation);
            }
          }

          if (bones[i].HasMember("scales")) {
            SizeType scaSize = bones[i]["scales"].Size();
            for (uint32 j = 0; j < scaSize; j += 4) {
              vec3 scale(1, 1, 1);
              uint32 keyFrame = bones[i]["scales"][j].GetUint();
              scale.x = bones[i]["scales"][j + 1].GetDouble();
              scale.y = bones[i]["scales"][j + 2].GetDouble();
              scale.z = bones[i]["scales"][j + 3].GetDouble();
              bone->AddScale(keyFrame, scale);
            }
          }
          if (parent != "")
            mesh->SetRootBone(bone);
          else {
            Ptr<Bone> p = mesh->GetRootBone()->Find(parent);
            if (p != nullptr)
              p->AddChild(bone);
          }
        }
      }
    }
  return mesh;
}

void Mesh::Render()
{
  uint32 numSubMeshes = mSubmeshes.Size();
  for (uint32 i = 0; i < numSubMeshes; i++)
    mSubmeshes[i]->Render();
}