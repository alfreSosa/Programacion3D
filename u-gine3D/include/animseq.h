#ifndef UGINE_ANIMSEQ_H
#define UGINE_ANIMSEQ_H

#include "types.h"
#include "string.h"

class AnimSeq {
public:
  AnimSeq() : mName(""), mFirstFrame(0), mLastFrame(0) { }
  AnimSeq(const String& name, uint32 firstFrame, uint32 lastFrame) : mName(name), mFirstFrame(firstFrame), mLastFrame(lastFrame) { }
  const String& GetName() const { return mName; }
  uint32 GetFirstFrame() const { return mFirstFrame; }
  uint32 GetLastFrame() const { return mLastFrame; }
  int GetNumFrames() const { return mLastFrame - mFirstFrame; }
private:
  String mName;
  uint32 mFirstFrame;
  uint32 mLastFrame;
};

#endif