#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <abstract.h>
#include <string.h>
#include <errno.h>
#include <time.h>

// Style is always snakecase for C/Lua/static languages, and camelcase for C++/Java/C#/OOP languages.

/*
 *	One of the problems we'll have to deal with is that an archive made on x86-64 will not extract on x86, normally. [because we love pointers!]
 *	I don't know how RAR or 7z or normal DEFLATE (zip + some others) actually work, this is a 'for fun' module.
 *	Don't use this archive format for anything actually needed for something.
 *	Well, unless you **really** want to. But I wouldn't risk it until this is stable.
 *
 *		- BS
 */

char word_size;	//Size of the thing we're working with.
#ifdef __WAYPOINT
char drive_letter;
char drive_partition;
//Because we can have A:/, which is implied to be partition 0, but also A:1/, A:2/, B:/, 
//B:1/, C:/, C:1/. However, unlike a UNIX, Waypoint won't let you mount the same physical media in two places.
//You'll be able to link something to that device's root, but accessing it simply changes the CWD to that of the drive.
//Not quite the same as a symlink.
#endif


struct free_arc_file
{
	FileSize_t filesize;
	int8_t file_name[256];
	struct free_arc_file* parent;	//Folder which contains this. If 'nullptr', it's parent is root of archive.
	int64_t num_children;
	struct free_arc_file** children;	//If this is a folder, then these point to it's children.
}free_arc_file;

struct freearc_header
{
	char far_header[4];
	char cpu_arch;
	wchar_t (*file_names)[256];
	char* operating_system;
	int64_t num_files;
	uint64_t* file_pointers;
	uint64_t archive_creation_time;
	uint64_t archive_checksum;
}freearc_header;

void println(const char* str)
{
	//I'm lazy. Sorry. I'll make this a macro or do something with it later. We're wasting a couple ops/sec for this.
	printf("%s\n", str);
}

void usage()
{
	println("Usage:");
	println("Place the name of the file you wish to extract after this command.");
	println("FLAGS:");
	println("-c for creating instead of extracting.");
	println("-r for output relative to the root of the operating system.");
	println("-a for processor architecture.");
	println("\tOptions are, \"amd64\", and \"x86\"");
	println("-? for this message.");
	if (!strcmp(OperatingSystem, "Waypoint"))
	{
		println("-d for output to root of a drive.");
	}
}

uint32_t hash(const void *buf, size_t buflength) 
{
	const uint8_t* buffer = (const uint8_t*)buf;
	uint64_t s1 = 1;
	uint64_t s2 = 0;
	for (size_t n = 0; n < buflength; n++) 
	{
		s1 = (s1 + buffer[n]) % 0x10000;
		s2 = (s2 + s1) % 0x10000;
	}     
	return (s2 << 16) | s1;
}

void create_archive(char* filename)
{
	FILE* archive = fopen(filename, "wb");

	
	struct freearc_header header;
	header.far_header[0] = 0x66;
	header.far_header[1] = 0x61; 
	header.far_header[2] = 0x72; 
	header.far_header[3] = 0x21;
	header.cpu_arch = CPUArch;
	header.operating_system = OperatingSystem;
	header.num_files = 0;
	header.archive_creation_time = (uint64_t)time(NULL);
	uint64_t filesize = 0;
	uint32_t hashv = hash(filename, strlen(filename));
	
	printf("%u\n", hashv);	
	fclose(archive);
}

void pack_archive(char* foldername)
{
	//Grab the folder, generate the header, and pack it up!!
}

struct freearc_header read_archive(char* filename)
{
	//Grabs the header of the archive...
}

void add_file_to_archive(char* archivename, FILE* file)
{
	
}

void unpack_archive(char* filename)
{
	//Create a folder with the same name as the archive save for the extensions.
	//Then rip the files out one by one...	
	char pos = strlen(filename);
	while (filename[pos] != '.' && pos > 0)
	{
		pos--;
	}
	int size_of_string = strlen(filename) - pos;
	char dirname[size_of_string];
	for (int i = 0; i < size_of_string; i++)
	{
		dirname[i] = filename[i];
		//std library can do this, what am I doing. strstr.
		//Oh well, it's written, don't worry about it if it works and it's fast enough for now.
	}
	CreateDirectory(dirname, 744);

	//TODO...
	FILE* archive = fopen(filename, "rb");
	
	//Generate the headers and filenames and all of that...
	
}

int add_file(char* filename, FILE* file)
{
	unpack_archive(filename);
	//TODO
	if (!strlen(filename))
	{
		return 0;
	}
	return 0;
}

int check_for_file(struct free_arc_file file)
{
	// Look for the parents of the file before going on...
	//TODO
	return 0;
	// If found, we return 1, otherwise 0.
}

void extract_file(struct free_arc_file file)
{
	//TODO
	if (sizeof(file))
	{
		return;
	}
	return;
}



int main(int argc, char* argv[])
{
	//We'll assume that you only have one option, and that you always have the filename immediately after the name of the program.
	//This is a bit of a dumb oversight... but maybe we'll add things like -o to specify output while making a new one or something???
	//Just don't use this in a weird way.	
	if (argc < 2)
	{
		usage();
		return -2;
	}
	word_size = sizeof(char);
	char* val = argv[1];
	if (!strcmp(val, "-c"))
	{
		if (argc < 4)
		{
			return -3;
		}
		FILE* archive_new = fopen(argv[3], "w");
  		fclose(archive_new);
	} 
	else if (!strcmp(val, "-r"))
	{

	} 
	else if (!strcmp(val, "-a"))
	{

	} 
	else if (!strcmp(val, "-?"))
	{
		usage();
		return 0;
	} 
	else if ((!strcmp(val, "-d") && !(strcmp(OperatingSystem, "Waypoint"))))
	{
		
	}
	//Above should exit/return when done. Here, extract the contents into a folder which is the hash of the file name + a "$freearc" signature at the end.
	//When the files are extracted completely, copy the contents perfectly over, then delete the cache folder.
	//The folder which is where the contents are stored is the same name as the archive except:
	/*
	 *	- We strip off __ALL__ extensions. If the archive is named 'foobar.tar.far.cmp", the folder is "foobar". It's wrong, but it's simpler.
	 *	- If the folder exists already, we name it the same thing but with a number added to the end. Ie, "foobar.far.cmp" --> "foobar (1)".
	 */

	//Detect all of the files, sort them out and all... blah blah blah.
	//Remember this is a toy archiving system, and is NOT meant for serious use.
	//Adding a file requires _de-archiving the whole thing_ and rearchiving.
	//Once that archive is made, we'll run a quick and dirty compression algo on it.
	//Thus, it's kinda comprable to tar.gz or tar.xz than zip or gzip. 	
	//If you want a real archiving system, just use 7zip or something, NOT FreedomArchive.
#ifdef __POSIX_SYS
	if (access(val, F_OK ) != -1 ) 
	{
		unpack_archive(val);
		return 0;
	} 
	return -3;
#else
	if (FileExists(val))
	{
		unpack_archive(val);
		return 0;
		// It exists...
	}
	return -3;
	//It doesn't...
#endif
}
