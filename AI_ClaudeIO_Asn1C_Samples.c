
/* 
 * ================= SEQUENCE OF =======================
 * For SEQUENCE OF constructs, asn1c generates a structure with an array and a count field:
 */
typedef struct SomeSequenceOf {
    A_SEQUENCE_OF(ElementType) list;
} SomeSequenceOf_t;


SomeSequenceOf_t *seq = calloc(1, sizeof(SomeSequenceOf_t));

// Add elements using asn_sequence_add()
ElementType_t *element = calloc(1, sizeof(ElementType_t));
// Initialize element...
asn_sequence_add(&seq->list, element);

// Access elements directly
for(int i = 0; i < seq->list.count; i++) {
    ElementType_t *elem = seq->list.array[i];
    // Access primitive fields within elem
}


/* 
 * ================= SET OF ==================
 * SET OF uses identical structure patterns to SEQUENCE OF:
 */
 
typedef struct SomeSetOf {
    A_SET_OF(ElementType) list;
} SomeSetOf_t;



/* 
 * ================ CHOICE ====================
 * For CHOICE constructs, asn1c generates a structure with a discriminator and a union:
 */
 
typedef struct SomeChoice {
    SomeChoice_PR present;
    union SomeChoice_u {
        OptionA_t optionA;
        OptionB_t optionB;
        // ... other options
    } choice;
} SomeChoice_t;

SomeChoice_t *choice = calloc(1, sizeof(SomeChoice_t));

// Set the choice variant
choice->present = SomeChoice_PR_optionA;
// Initialize the selected option
choice->choice.optionA.someField = value;

// When reading, check the discriminator first
switch(choice->present) {
    case SomeChoice_PR_optionA:
        // Access choice->choice.optionA fields
        break;
    case SomeChoice_PR_optionB:
        // Access choice->choice.optionB fields
        break;
    default:
        // Handle error
        break;
}

/* Nested Access Patterns
 * For deeply nested structures combining these constructs:
 */
// Example: SEQUENCE OF (CHOICE of primitives)
for(int i = 0; i < outerSeq->list.count; i++) {
    SomeChoice_t *choice = outerSeq->list.array[i];
    switch(choice->present) {
        case SomeChoice_PR_integerOption:
            long value = choice->choice.integerOption;
            break;
        case SomeChoice_PR_stringOption:
            char *str = (char*)choice->choice.stringOption.buf;
            break;
    }
}

