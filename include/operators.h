#ifndef ERA_OPERATORS_H
#define ERA_OPERATORS_H

#include "era_interpreter.h"

// NB: can't use identifier like 8_BIT, had to add F_ (Format) prefix
enum format_t {
	F_8_BIT,
	F_16_BIT,
	F_32_BIT,
};

/**
 * @brief Rj += Ri
 * Add content of registers i and j and store result in register j
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success
 */
int add(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj -= Ri
 * Substract content of registers i from register j and store result in register j
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success
 */
int sub(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = Ri >> 1
 * Arithmetically (preserving sign) shift contents of register i one bit right
 * and store result into register j
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success
 */
int asr(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

/**
 * @brief Rj = Ri << 1
 * Arithmetically (preserving sign) shift contents of register i one bit left
 * and store result into register j
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success
 */
int asl(struct era_t *era, uint8_t i, uint8_t j, enum format_t format);

#endif /* ifndef ERA_OPERATORS_H */
