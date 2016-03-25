#include <linux/random.h>

/* Hard coded answers */
const char* answers[] = {
	"It is certain\n",
	"It is decidedly so\n",
	"Without a doubt\n",
	"Yes definitely\n",
	"You may rely on it\n",
	"As I see it, yes\n",
	"Most likely\n",
	"Outlook good\n",
	"Yes\n",
	"Signs point to yes\n",
	"Reply hazy try again\n",
	"Ask again later\n",
	"Better not tell you now\n",
	"Cannot predict now\n",
	"Concentrate and ask again\n",
	"Don't count on it\n",
	"My reply is no\n",
	"My sources say no\n",
	"Outlook not so good\n",
	"Very doubtful\n"
};

#define answer_no (sizeof (answers) / sizeof (const char *))

static inline void choose_answers(char *buf, ssize_t size)
{
	int rand = 0;
	get_random_bytes(&rand, sizeof(rand));
	int rand_answer = rand % answer_no;

	memset(buf, 0, size);
	memcpy(buf, answers[rand_answer], strlen(answers[rand_answer]));
}


