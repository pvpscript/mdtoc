#include <stdio.h>
#include <string.h>

#include "file.h"
#include "fileutils.h"

#define START_LINE      "[//]: #mdtoc_start"
#define END_LINE        "[//]: #mdtoc_end" 

#define MAX(x, y) ((x) > (y)) ? (x) : (y)

struct file_info {
        long offset_start;
        long offset_end;
};

static long parse_section(FILE *fp, char *section)
{
        size_t section_len = strlen(section);
        char buf[section_len + 1 /* \n */ + 1 /* \0 */];
        long curr_offset;
        size_t buf_temp_len;
        char w;

        for (;;) {
                curr_offset = ftell(fp);
                if (fgets(buf, sizeof buf, fp))
                        buf_temp_len = ftell(fp) - curr_offset;
                else
                        break;

                if (buf[buf_temp_len - 1] == '\n') {
                        if (section_len == buf_temp_len - 1 &&
                                        !strncmp(buf, section, section_len - 1))
                                return ftell(fp); /* offset position */
                        continue;
                }

                while((w = fgetc(fp)) != '\n')
                        ;
        }

        return -1;
}

void parse_file(struct file *f)
{
        FILE *fp = get_file_pointer(f);
        struct file_info info;
        
        info.offset_start = parse_section(fp, START_LINE);
        info.offset_end = parse_section(fp, END_LINE);

        printf("Bytes offset for the beginning: %ld\n", info.offset_start);
        printf("Bytes offset for the end: %ld\n", info.offset_end);
}


int main(int argc, char **argv)
{
        struct file *f = open_file("./test.md");
        parse_file(f);
        exit(0);
        char *message = "This is a very cool message!\n";
        /*char *loren = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce ullamcorper quam mauris, at posuere augue posuere non. Sed iaculis elit et placerat dictum. Nam faucibus venenatis ex. Nullam tempor eros vel lectus gravida tincidunt. Phasellus tincidunt, nisl eget porttitor rhoncus, neque tellus aliquam massa, in ultrices est metus ac sapien. Nam dignissim ipsum diam, vel efficitur nisi placerat vitae. Morbi auctor tellus non ipsum efficitur fringilla id nec ex. Ut lectus magna, laoreet cursus erat at, iaculis egestas nisi. In euismod nisl eu tortor porttitor, vel euismod eros faucibus. Nullam enim quam, iaculis sed nunc euismod, euismod interdum metus. Mauris tristique odio dui, sit amet aliquam mauris ultricies vel. Aliquam condimentum ornare metus, ac blandit nibh elementum at. Curabitur maximus velit rutrum, vestibulum felis sed, dignissim enim. Nam laoreet, nunc eget condimentum viverra, ipsum tortor ullamcorper lorem, a iaculis metus sapien congue risus. Suspendisse sapien diam, rutrum a nulla convallis, sagittis porta justo. Quisque id viverra dolor. Aenean eu convallis mauris, quis rhoncus leo. Nunc tincidunt nibh sed faucibus tempor. Nulla vitae dictum augue, vel ultrices purus. Aliquam efficitur magna nec metus rhoncus molestie. Fusce eget dolor est. Aenean accumsan condimentum ipsum, ac molestie nibh euismod ac. Proin iaculis volutpat diam, at varius libero pretium duis.\n"; */
        char *fonky_chonky = "Do you want the fonky chonky?\n";

/*        advance_file(f, fonky_chonky, 37);*/
        shrink_file(f, strlen(fonky_chonky), 37);

        close_file(f);

        return 0;
}
