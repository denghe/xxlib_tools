#pragma once
AJSON(FileExts::LockPoint, x, y);
AJSON(FileExts::CDCircle, x, y, r);
AJSON(FileExts::TimePoint_LockPoints, time, mainLockPoint, lockPoints);
AJSON(FileExts::TimePoint_CDCircles, time, maxCDCircle, cdCircles);
AJSON(FileExts::TimePoint_Speed, time, speed);
AJSON(FileExts::TimePoint_Frame, time, picName);
AJSON(FileExts::Action, name, totalSeconds, lps, cds, ss, fs);
AJSON(FileExts::PathwayPoint, x, y, tension, numSegments);
AJSON(FileExts::File_Anim, actions);
AJSON(FileExts::File_pathway, isLoop, points);
