#ifndef ERA_MATH_OPERATORS_H
#define ERA_MATH_OPERATORS_H

#include "era_interpreter.h"

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
int add(struct era_t *era, sword_t i, sword_t j, enum format_t format);

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
int sub(struct era_t *era, sword_t i, sword_t j, enum format_t format);

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
int asr(struct era_t *era, sword_t i, sword_t j, enum format_t format);

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
int asl(struct era_t *era, sword_t i, sword_t j, enum format_t format);

#endif /* ifndef ERA_MATH_OPERATORS_H */
