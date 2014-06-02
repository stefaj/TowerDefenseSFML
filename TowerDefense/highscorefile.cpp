#include "highscorefile.h"


HighScoreFile::HighScoreFile(string fileName)
{
    filename = fileName;
    ReadAll();
}

void HighScoreFile::WriteHighscore(std::string user, int score)
{
    Highscore s;
    s.user = user;
    s.score = score;
    WriteHighscore(s);
}

void HighScoreFile::WriteHighscore(Highscore score)
{
    scores.push_back(score);
    SortScores();

	ofstream file;
	file.open(filename);

    for(int i = 0; i < scores.size(); i++)
    {
        Highscore curScore = scores[i];
		file << curScore.user << "," << curScore.score << "\n";

    }

    file.close();
}

const std::vector<Highscore> HighScoreFile::GetScores()
{
    return scores;
}

void HighScoreFile::SortScores()
{
    std::sort (scores.begin(), scores.end(), CompareHighscore());
}

void HighScoreFile::ReadAll()
{
	scores.clear();

	string line;
	ifstream file(filename);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			Highscore h;
			h.user = line.substr(0, line.find_first_of(','));
			string score = line.substr(line.find_first_of(',')+1);

			h.score = atoi(score.c_str());

			scores.push_back(h);
		}
		file.close();
	}
	else
	{
		//Some error
	}

	SortScores();
}
