
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 100
#define BUF_SIZE_MID 30
#define BUF_SIZE_SMALL 10

////////////////////////////////////////////////////////////

typedef int32_t Note;
enum {NIL = -1, I = 0, bII, II, bIII, III, IV, bV, V, bVI, VI, bVII, VII};

int noteToNum(Note a)
{
	switch (a)
	{
		case I:
			return 1;
		case II:
			return 2;
		case III:
			return 3;
		case IV:
			return 4;
		case V:
			return 5;
		case VI:
			return 6;
		case VII:
			return 7;
		default:
			return 0;
	}
}

char* noteToString(Note a)
{
	switch (a)
	{
		case I:
			return "1";
		case bII:
			return "b2";
		case II:
			return "2";
		case bIII:
			return "b3";
		case III:
			return "3";
		case IV:
			return "4";
		case bV:
			return "b5";
		case V:
			return "5";
		case bVI:
			return "b6";
		case VI:
			return "6";
		case bVII:
			return "b7";
		case VII:
			return "7";
		default:
			return "ErrorNote";
	}
}

Note normalize(Note a)
{
	if (a >= 0)
	{ return a % 12; }
	else
	{ return (a % 12) + 12; }
}

////////////////////////////////////////////////////////////

typedef struct
{
	int len;
	Note* notes;
} Path;

Path* Path_new()
{
	Path* ret = malloc(sizeof(Path));
	
	ret->len = 0;
	ret->notes = malloc(BUF_SIZE_SMALL * sizeof(Note));
	for (int i = 0; i < BUF_SIZE_SMALL; i++)
	{ ret->notes[i] = NIL; }

	return ret;
}

void Path_free(Path* p)
{
	free(p->notes);
	free(p);
}

void Path_addNote(Path* p, Note note)
{
	p->notes[p->len] = note;
	p->len++;
}

void Path_print(Path* p)
{
	for (int i = 0; i < p->len; i++)
	{
		if (i > 0) printf(":");
		printf("%d", noteToNum(p->notes[i]));
	}
}

////////////////////////////////////////////////////////////

typedef struct
{
	int len;
	Path** paths;
} PathList;

PathList* PathList_new()
{
	PathList* ret = malloc(sizeof(PathList));
	
	ret->len = 0;
	ret->paths = malloc(BUF_SIZE_MID * sizeof(Path*));
	for (int i = 0; i < BUF_SIZE_MID; i++)
	{ ret->paths[i] = NULL; }

	return ret;
}

void PathList_free(PathList* pl)
{
	for (int i = 0; i < pl->len; i++)
	{
		free(pl->paths[i]);
		pl->paths[i] = NULL;
	}

	free(pl);
}

void PathList_addPath(PathList* pl, Path* path)
{
	pl->paths[pl->len] = path;
	pl->len++;
}

void PathList_print(PathList* pl)
{
	printf("[\n");
	for (int i = 0; i < pl->len; i++)
	{
		printf("  ");
		Path_print(pl->paths[i]);
		printf("\n");
	}
	printf("]\n");
}

////////////////////////////////////////////////////////////

typedef enum {NIL_CHORD_TYPE, MAJOR, MINOR, DIMINISHED} ChordType;

ChordType getChordType(Note a)
{
	switch (a)
	{
		case II:
			return MINOR;
		case III:
			return MINOR;
		case IV:
			return MAJOR;
		case V:
			return MAJOR;
		case VI:
			return MINOR;
		case VII:
			return DIMINISHED;
		default:
			return NIL_CHORD_TYPE;
	}
}

////////////////////////////////////////////////////////////

int main(void)
{
	const Note scaleNotes[7] = {I, II, III, IV, V, VI, VII};

	PathList* maj[12];
	PathList* min[12];
	PathList* dim[12];

	for (int i = 0; i < 12; i++)
	{
		maj[i] = PathList_new();
		min[i] = PathList_new();
		dim[i] = PathList_new();
	}

/*
	// degree 2, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}

	// degree 3, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}
*/

///*
	// degree 2, everything
	for (int i = 1; i < 7; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}

	// degree 3, everything
	for (int i = 1; i < 7; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			for (int k = 1; k < 7; k++)
			{
				Note kSn = scaleNotes[k];

				Path* path = Path_new();
				Path_addNote(path, iSn);
				Path_addNote(path, jSn);
				Path_addNote(path, kSn);

				Note tonicRelation = normalize(iSn + jSn + kSn);
				switch (getChordType(kSn))
				{
					case MAJOR:
						PathList_addPath(maj[tonicRelation], path);
						break;
					case MINOR:
						PathList_addPath(min[tonicRelation], path);
						break;
					case DIMINISHED:
						PathList_addPath(dim[tonicRelation], path);
						break;
				}
			}
		}
	}
//*/

/*
	// degree 4, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + iSn + iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}

	// degree 5, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + iSn + iSn + iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}

	// degree 6, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + iSn + iSn + iSn + iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}

	// degree 7, only 4ths & 5ths
	for (int i = 3; i <= 4; i++)
	{
		Note iSn = scaleNotes[i];

		for (int j = 1; j < 7; j++)
		{
			Note jSn = scaleNotes[j];

			Path* path = Path_new();
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, iSn);
			Path_addNote(path, jSn);

			Note tonicRelation = normalize(iSn + iSn + iSn + iSn + iSn + iSn + jSn);
			switch (getChordType(jSn))
			{
				case MAJOR:
					PathList_addPath(maj[tonicRelation], path);
					break;
				case MINOR:
					PathList_addPath(min[tonicRelation], path);
					break;
				case DIMINISHED:
					PathList_addPath(dim[tonicRelation], path);
					break;
			}
		}
	}
*/

	printf("--Major--\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%s:\n", noteToString(i));
		PathList_print(maj[i]);
	}

	printf("--Minor--\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%s:\n", noteToString(i));
		PathList_print(min[i]);
	}

	printf("--Diminished--\n");
	for (int i = 0; i < 12; i++)
	{
		printf("%s:\n", noteToString(i));
		PathList_print(dim[i]);
	}

	for (int i = 0; i < 12; i++)
	{
		PathList_free(maj[i]);
		PathList_free(min[i]);
		PathList_free(dim[i]);
	}

	return 0;
}