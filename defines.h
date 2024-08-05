#define UDP 0
#define UDP_TIMESTAMP 1
#define TCP 2

#define PORT 42069
#define PROTOCOL UDP // TODO: Only udp implemented so far
#define MTU 512
#define MAX_THREADS 7
#define MAX_WORK_PER_THREAD 2
#define MAX_CLIENTS (MAX_THREADS * MAX_WORK_PER_THREAD)
#define REQUEST_QUEUE_SIZE 5 // Chosen arbitrarily, TODO: if needed figure out good size

#define REQUEST_SIZE 4
// request : 4 byte id for movie/tv episode/song | 
// first byte 0 reserved for status requests
// first byte 1 reserved for movies
// first byte 2 - 4 reserved for tv show episodes
// first byte 5 - F reserved for songs
#define STATUS_STOP 0x0000 // stop serving client
#define STATUS_KEEP_ALIVE 0x0001 // if not received within TIMEOUT minutes, stream is killed
#define STATUS_TOGGLE_PAUSE 0x0002 // pause/unpause stream

#define TIMEOUT 5*60 // timeout in seconds

#define MEDIA_PATH "media/"