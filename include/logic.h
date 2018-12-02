#ifndef ERA_LOGIC_H
#define ERA_LOGIC_H

#include "era_interpreter.h"

/**
 * @brief Rj BITWISE OR Ri
 * Applies the OR operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t or(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj BITWISE AND Ri
 * Applies the AND operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t and(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj BITWISE XOR Ri
 * Applies the XOR operator to every bit of Rj and Ri and stores the result in Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t xor(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief Rj = Ri << 1
 * Logically shifts the contents of Ri one bit left and puts it into Rj
 * The rightmost bit of the shifted value is lost in Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t lsl(struct era_t *era, sword_t i, sword_t j, enum format_t format);

/**
 * @brief *Rj >> *Ri
 * Logically shifts the contents of Ri one bit right and puts it into Rj
 * The leftmost bit of the shifted value is lost in Rj
 *
 * @param[in] era - pointer to era structure
 * @param[in] i	- no. of register
 * @param[in] j	- no. of register
 * @param[in] format - operation format
 *
 * @returns 0 on success, error code "MEMORY_ERROR_*" on error
 */
sword_t lsr(struct era_t *era, sword_t i, sword_t j, enum format_t format);

#endif //ERA_LOGIC_H
