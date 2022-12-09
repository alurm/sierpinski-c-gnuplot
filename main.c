/*
Copyright (c) 2022 Alan Urmancheev <alan.urman@gmail.com>

Permission to use, copy, modify, and distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double x;
	double y;
} my_point_t;

my_point_t verticies[] = { { 1, 1 }, { 3, 5 }, { 5, 1 } };
my_point_t current_point;
#define N_VERTICIES (sizeof verticies / sizeof *verticies)
int iterations = 100000;
#define DEPTH 3

static my_point_t my_random_vertex(void) {
	return verticies[rand() % (sizeof verticies / sizeof *verticies)];
}

static my_point_t my_between(my_point_t a, my_point_t b) {
	return (my_point_t){
		.x = (a.x + b.x) / 2,
		.y = (a.y + b.y) / 2,
	};
}

static void print_point(my_point_t p) {
	printf("%f %f\n", p.x, p.y);
}

int main(void) {
	current_point = my_between(verticies[0], verticies[1]);
	for (int depth = 0; depth < DEPTH; depth++) {
		for (int i = 0; i < iterations; i++) {
			current_point = my_between(current_point, my_random_vertex());
			print_point(current_point);
		}
		my_point_t tmp_verticies[sizeof verticies / sizeof *verticies];
		for (int i = 0; i < (sizeof verticies / sizeof *verticies); i++) {
			tmp_verticies[i] = my_between(
				verticies[i],
				verticies[(i + 1) % N_VERTICIES]
			);
		}
		for (int i = 0; i < N_VERTICIES; i++) {
			verticies[i] = tmp_verticies[i];
		}
		current_point = my_between(verticies[0], verticies[1]);
		iterations /= 3;
	}
}
