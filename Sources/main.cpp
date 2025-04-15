#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <vector>


int main(int argc, char *argv[])
{
    // 입력 파일이 없는 경우 오류 메시지 출력
    if (argc < 2) {
        fprintf(stderr, "[%s]: 파일을 한 개 이상 입력해주세요.", argv[0]);
        return 1;
    }

    uint32_t total_sum = 0;
    std::vector<uint32_t> numbers; // 각 파일에서 읽은 숫자

    for (int i = 1; i < argc; i++) {
        FILE* fp = fopen(argv[i], "rb");
        // 파일 열기 실패한 경우
        if (!fp) {
            fprintf(stderr, "%s 파일을 열 수 없습니다.\n", argv[i]);
            return 1;
        }

        uint32_t num;
        size_t read_size = fread(&num, sizeof(uint32_t), 1, fp);

        // 파일의 크기가 4바이트보다 작아 제대로 읽지 못한 경우
        if (read_size != 1) {
            fprintf(stderr, "%s: 파일 크기가 너무 작습니다. 최소 4바이트 이상이어야 합니다.\n", argv[i]);
            fclose(fp);
            return 1;
        }

        num = ntohl(num);
        numbers.push_back(num);
        total_sum += num;

        fclose(fp);

    }

    // 결과 출력
    for (size_t i = 0; i < numbers.size(); i++) {
        printf("%u(0x%08x)", numbers[i], numbers[i]);
        if (i != numbers.size() - 1)
            printf(" + ");
    }
    printf(" = %u(0x%08x)\n", total_sum, total_sum);

    return 0;


}
