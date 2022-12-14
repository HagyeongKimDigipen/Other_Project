/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Purpose: Header file for Animation Module
Project: CS230
Author: Kevin Wright
Creation date: 3/15/2020
-----------------------------------------------------------------*/
#pragma once
#include <vector>	// std::vector

class Animation {
public:
	Animation();
	Animation(std::string file);
	~Animation();
	void Update(double dt);
	int GetDisplayFrame();
	void Reset();
	bool IsAnimationDone();
private:
	enum class Command {
		PlayFrame,
		Loop,
		End,
	};
	class CommandData {
	public:
		virtual ~CommandData() {}
		virtual Command GetType() = 0;
	};
	class PlayFrame : public CommandData {
	public:
		PlayFrame(int frame, double duration);
		Command GetType() override { return Command::PlayFrame; }
		void Update(double dt);
		bool IsFrameDone();
		void Reset();
		int GetFrameNum();
	private:
		int frame;
		double targetTime;
		double timer;
	};
	class Loop : public CommandData {
	public:
		Loop(int loopToIndex);
		Command GetType() override { return Command::Loop; }
		int GetLoopToIndex();
	private:
		int loopToIndex;
	};
	class End : public CommandData {
	public:
		Command GetType() override { return Command::End; }
	private:
	};

	bool isAnimationDone;
	int animSequenceIndex;
	PlayFrame* currPlayFrameData;
	std::vector<CommandData*> animation;
};