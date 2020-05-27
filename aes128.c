#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>
#include <emmintrin.h>
#include <time.h>

typedef unsigned char uint8;
typedef unsigned int uint32;

uint8 S_BOX_01[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

uint8 S_BOX_02[256] = {
    0xc6, 0xf8, 0xee, 0xf6, 0xff, 0xd6, 0xde, 0x91, 0x60, 0x02, 0xce, 0x56, 0xe7, 0xb5, 0x4d, 0xec,
    0x8f, 0x1f, 0x89, 0xfa, 0xef, 0xb2, 0x8e, 0xfb, 0x41, 0xb3, 0x5f, 0x45, 0x23, 0x53, 0xe4, 0x9b,
    0x75, 0xe1, 0x3d, 0x4c, 0x6c, 0x7e, 0xf5, 0x83, 0x68, 0x51, 0xd1, 0xf9, 0xe2, 0xab, 0x62, 0x2a,
    0x08, 0x95, 0x46, 0x9d, 0x30, 0x37, 0x0a, 0x2f, 0x0e, 0x24, 0x1b, 0xdf, 0xcd, 0x4e, 0x7f, 0xea,
    0x12, 0x1d, 0x58, 0x34, 0x36, 0xdc, 0xb4, 0x5b, 0xa4, 0x76, 0xb7, 0x7d, 0x52, 0xdd, 0x5e, 0x13,
    0xa6, 0xb9, 0x00, 0xc1, 0x40, 0xe3, 0x79, 0xb6, 0xd4, 0x8d, 0x67, 0x72, 0x94, 0x98, 0xb0, 0x85,
    0xbb, 0xc5, 0x4f, 0xed, 0x86, 0x9a, 0x66, 0x11, 0x8a, 0xe9, 0x04, 0xfe, 0xa0, 0x78, 0x25, 0x4b,
    0xa2, 0x5d, 0x80, 0x05, 0x3f, 0x21, 0x70, 0xf1, 0x63, 0x77, 0xaf, 0x42, 0x20, 0xe5, 0xfd, 0xbf,
    0x81, 0x18, 0x26, 0xc3, 0xbe, 0x35, 0x88, 0x2e, 0x93, 0x55, 0xfc, 0x7a, 0xc8, 0xba, 0x32, 0xe6,
    0xc0, 0x19, 0x9e, 0xa3, 0x44, 0x54, 0x3b, 0x0b, 0x8c, 0xc7, 0x6b, 0x28, 0xa7, 0xbc, 0x16, 0xad,
    0xdb, 0x64, 0x74, 0x14, 0x92, 0x0c, 0x48, 0xb8, 0x9f, 0xbd, 0x43, 0xc4, 0x39, 0x31, 0xd3, 0xf2,
    0xd5, 0x8b, 0x6e, 0xda, 0x01, 0xb1, 0x9c, 0x49, 0xd8, 0xac, 0xf3, 0xcf, 0xca, 0xf4, 0x47, 0x10,
    0x6f, 0xf0, 0x4a, 0x5c, 0x38, 0x57, 0x73, 0x97, 0xcb, 0xa1, 0xe8, 0x3e, 0x96, 0x61, 0x0d, 0x0f,
    0xe0, 0x7c, 0x71, 0xcc, 0x90, 0x06, 0xf7, 0x1c, 0xc2, 0x6a, 0xae, 0x69, 0x17, 0x99, 0x3a, 0x27,
    0xd9, 0xeb, 0x2b, 0x22, 0xd2, 0xa9, 0x07, 0x33, 0x2d, 0x3c, 0x15, 0xc9, 0x87, 0xaa, 0x50, 0xa5,
    0x03, 0x59, 0x09, 0x1a, 0x65, 0xd7, 0x84, 0xd0, 0x82, 0x29, 0x5a, 0x1e, 0x7b, 0xa8, 0x6d, 0x2c};

uint8 S_BOX_03[256] = {
    0xa5, 0x84, 0x99, 0x8d, 0x0d, 0xbd, 0xb1, 0x54, 0x50, 0x03, 0xa9, 0x7d, 0x19, 0x62, 0xe6, 0x9a,
    0x45, 0x9d, 0x40, 0x87, 0x15, 0xeb, 0xc9, 0x0b, 0xec, 0x67, 0xfd, 0xea, 0xbf, 0xf7, 0x96, 0x5b,
    0xc2, 0x1c, 0xae, 0x6a, 0x5a, 0x41, 0x02, 0x4f, 0x5c, 0xf4, 0x34, 0x08, 0x93, 0x73, 0x53, 0x3f,
    0x0c, 0x52, 0x65, 0x5e, 0x28, 0xa1, 0x0f, 0xb5, 0x09, 0x36, 0x9b, 0x3d, 0x26, 0x69, 0xcd, 0x9f,
    0x1b, 0x9e, 0x74, 0x2e, 0x2d, 0xb2, 0xee, 0xfb, 0xf6, 0x4d, 0x61, 0xce, 0x7b, 0x3e, 0x71, 0x97,
    0xf5, 0x68, 0x00, 0x2c, 0x60, 0x1f, 0xc8, 0xed, 0xbe, 0x46, 0xd9, 0x4b, 0xde, 0xd4, 0xe8, 0x4a,
    0x6b, 0x2a, 0xe5, 0x16, 0xc5, 0xd7, 0x55, 0x94, 0xcf, 0x10, 0x06, 0x81, 0xf0, 0x44, 0xba, 0xe3,
    0xf3, 0xfe, 0xc0, 0x8a, 0xad, 0xbc, 0x48, 0x04, 0xdf, 0xc1, 0x75, 0x63, 0x30, 0x1a, 0x0e, 0x6d,
    0x4c, 0x14, 0x35, 0x2f, 0xe1, 0xa2, 0xcc, 0x39, 0x57, 0xf2, 0x82, 0x47, 0xac, 0xe7, 0x2b, 0x95,
    0xa0, 0x98, 0xd1, 0x7f, 0x66, 0x7e, 0xab, 0x83, 0xca, 0x29, 0xd3, 0x3c, 0x79, 0xe2, 0x1d, 0x76,
    0x3b, 0x56, 0x4e, 0x1e, 0xdb, 0x0a, 0x6c, 0xe4, 0x5d, 0x6e, 0xef, 0xa6, 0xa8, 0xa4, 0x37, 0x8b,
    0x32, 0x43, 0x59, 0xb7, 0x8c, 0x64, 0xd2, 0xe0, 0xb4, 0xfa, 0x07, 0x25, 0xaf, 0x8e, 0xe9, 0x18,
    0xd5, 0x88, 0x6f, 0x72, 0x24, 0xf1, 0xc7, 0x51, 0x23, 0x7c, 0x9c, 0x21, 0xdd, 0xdc, 0x86, 0x85,
    0x90, 0x42, 0xc4, 0xaa, 0xd8, 0x05, 0x01, 0x12, 0xa3, 0x5f, 0xf9, 0xd0, 0x91, 0x58, 0x27, 0xb9,
    0x38, 0x13, 0xb3, 0x33, 0xbb, 0x70, 0x89, 0xa7, 0xb6, 0x22, 0x92, 0x20, 0x49, 0xff, 0x78, 0x7a,
    0x8f, 0xf8, 0x80, 0x17, 0xda, 0x31, 0xc6, 0xb8, 0xc3, 0xb0, 0x77, 0x11, 0xcb, 0xfc, 0xd6, 0x3a};

uint8 S_BOX_I_09[256] = {
    0xf4, 0x41, 0x17, 0x27, 0xab, 0x9d, 0xfa, 0xe3, 0x30, 0x76, 0xcc, 0x02, 0xe5, 0x2a, 0x35, 0x62,
    0xb1, 0xba, 0xea, 0xfe, 0x2f, 0x4c, 0x46, 0xd3, 0x8f, 0x92, 0x6d, 0x52, 0xbe, 0x74, 0xe0, 0xc9,
    0xc2, 0x8e, 0x58, 0xb9, 0xe1, 0x88, 0x20, 0xce, 0xdf, 0x1a, 0x51, 0x53, 0x64, 0x6b, 0x81, 0x08,
    0x48, 0x45, 0xde, 0x7b, 0x73, 0x4b, 0x1f, 0x55, 0xeb, 0xb5, 0xc5, 0x37, 0x28, 0xbf, 0x03, 0x16,
    0xcf, 0x79, 0x07, 0x69, 0xda, 0x05, 0x34, 0xa6, 0x2e, 0xf3, 0x8a, 0xf6, 0x83, 0x60, 0x71, 0x6e,
    0x21, 0xdd, 0x3e, 0xe6, 0x54, 0xc4, 0x06, 0x50, 0x98, 0xbd, 0x40, 0xd9, 0xe8, 0x89, 0x19, 0xc8,
    0x7c, 0x42, 0x84, 0x00, 0x80, 0x2b, 0x11, 0x5a, 0x0e, 0x85, 0xae, 0x2d, 0x0f, 0x5c, 0x5b, 0x36,
    0x0a, 0x57, 0xee, 0x9b, 0xc0, 0xdc, 0x77, 0x12, 0x93, 0xa0, 0x22, 0x1b, 0x09, 0x8b, 0xb6, 0x1e,
    0xf1, 0x75, 0x99, 0x7f, 0x01, 0x72, 0x66, 0xfb, 0x43, 0x23, 0xed, 0xe4, 0x31, 0x63, 0x97, 0xc6,
    0x4a, 0xbb, 0xf9, 0x29, 0x9e, 0xb2, 0x86, 0xc1, 0xb3, 0x70, 0x94, 0xe9, 0xfc, 0xf0, 0x7d, 0x33,
    0x49, 0x38, 0xca, 0xd4, 0xf5, 0x7a, 0xb7, 0xad, 0x3a, 0x78, 0x5f, 0x7e, 0x8d, 0xd8, 0x39, 0xc3,
    0x5d, 0xd0, 0xd5, 0x25, 0xac, 0x18, 0x9c, 0x3b, 0x26, 0x59, 0x9a, 0x4f, 0x95, 0xff, 0xbc, 0x15,
    0xe7, 0x6f, 0x9f, 0xb0, 0xa4, 0x3f, 0xa5, 0xa2, 0x4e, 0x82, 0x90, 0xa7, 0x04, 0xec, 0xcd, 0x91,
    0x4d, 0xef, 0xaa, 0x96, 0xd1, 0x6a, 0x2c, 0x65, 0x5e, 0x8c, 0x87, 0x0b, 0x67, 0xdb, 0x10, 0xd6,
    0xd7, 0xa1, 0xf8, 0x13, 0xa9, 0x61, 0x1c, 0x47, 0xd2, 0xf2, 0x14, 0xc7, 0xf7, 0xfd, 0x3d, 0x44,
    0xaf, 0x68, 0x24, 0xa3, 0x1d, 0xe2, 0x3c, 0x0d, 0xa8, 0x0c, 0xb4, 0x56, 0xcb, 0x32, 0x6c, 0xb8};

uint8 S_BOX_I_0B[256] = {
    0x50, 0x53, 0xc3, 0x96, 0xcb, 0xf1, 0xab, 0x93, 0x55, 0xf6, 0x91, 0x25, 0xfc, 0xd7, 0x80, 0x8f,
    0x49, 0x67, 0x98, 0xe1, 0x02, 0x12, 0xa3, 0xc6, 0xe7, 0x95, 0xeb, 0xda, 0x2d, 0xd3, 0x29, 0x44,
    0x6a, 0x78, 0x6b, 0xdd, 0xb6, 0x17, 0x66, 0xb4, 0x18, 0x82, 0x60, 0x45, 0xe0, 0x84, 0x1c, 0x94,
    0x58, 0x19, 0x87, 0xb7, 0x23, 0xe2, 0x57, 0x2a, 0x07, 0x03, 0x9a, 0xa5, 0xf2, 0xb2, 0xba, 0x5c,
    0x2b, 0x92, 0xf0, 0xa1, 0xcd, 0xd5, 0x1f, 0x8a, 0x9d, 0xa0, 0x32, 0x75, 0x39, 0xaa, 0x06, 0x51,
    0xf9, 0x3d, 0xae, 0x46, 0xb5, 0x05, 0x6f, 0xff, 0x24, 0x97, 0xcc, 0x77, 0xbd, 0x88, 0x38, 0xdb,
    0x47, 0xe9, 0xc9, 0x00, 0x83, 0x48, 0xac, 0x4e, 0xfb, 0x56, 0x1e, 0x27, 0x64, 0x21, 0xd1, 0x3a,
    0xb1, 0x0f, 0xd2, 0x9e, 0x4f, 0xa2, 0x69, 0x16, 0x0a, 0xe5, 0x43, 0x1d, 0x0b, 0xad, 0xb9, 0xc8,
    0x85, 0x4c, 0xbb, 0xfd, 0x9f, 0xbc, 0xc5, 0x34, 0x76, 0xdc, 0x68, 0x63, 0xca, 0x10, 0x40, 0x20,
    0x7d, 0xf8, 0x11, 0x6d, 0x4b, 0xf3, 0xec, 0xd0, 0x6c, 0x99, 0xfa, 0x22, 0xc4, 0x1a, 0xd8, 0xef,
    0xc7, 0xc1, 0xfe, 0x36, 0xcf, 0x28, 0x26, 0xa4, 0xe4, 0x0d, 0x9b, 0x62, 0xc2, 0xe8, 0x5e, 0xf5,
    0xbe, 0x7c, 0xa9, 0xb3, 0x3b, 0xa7, 0x6e, 0x7b, 0x09, 0xf4, 0x01, 0xa8, 0x65, 0x7e, 0x08, 0xe6,
    0xd9, 0xce, 0xd4, 0xd6, 0xaf, 0x31, 0x30, 0xc0, 0x37, 0xa6, 0xb0, 0x15, 0x4a, 0xf7, 0x0e, 0x2f,
    0x8d, 0x4d, 0x54, 0xdf, 0xe3, 0x1b, 0xb8, 0x7f, 0x04, 0x5d, 0x73, 0x2e, 0x5a, 0x52, 0x33, 0x13,
    0x8c, 0x7a, 0x8e, 0x89, 0xee, 0x35, 0xed, 0x3c, 0x59, 0x3f, 0x79, 0xbf, 0xea, 0x5b, 0x14, 0x86,
    0x81, 0x3e, 0x2c, 0x5f, 0x72, 0x0c, 0x8b, 0x41, 0x71, 0xde, 0x9c, 0x90, 0x61, 0x70, 0x74, 0x42};

uint8 S_BOX_I_0D[256] = {
    0xa7, 0x65, 0xa4, 0x5e, 0x6b, 0x45, 0x58, 0x03, 0xfa, 0x6d, 0x76, 0x4c, 0xd7, 0xcb, 0x44, 0xa3,
    0x5a, 0x1b, 0x0e, 0xc0, 0x75, 0xf0, 0x97, 0xf9, 0x5f, 0x9c, 0x7a, 0x59, 0x83, 0x21, 0x69, 0xc8,
    0x89, 0x79, 0x3e, 0x71, 0x4f, 0xad, 0xac, 0x3a, 0x4a, 0x31, 0x33, 0x7f, 0x77, 0xae, 0xa0, 0x2b,
    0x68, 0xfd, 0x6c, 0xf8, 0xd3, 0x02, 0x8f, 0xab, 0x28, 0xc2, 0x7b, 0x08, 0x87, 0xa5, 0x6a, 0x82,
    0x1c, 0xb4, 0xf2, 0xe2, 0xf4, 0xbe, 0x62, 0xfe, 0x53, 0x55, 0xe1, 0xeb, 0xec, 0xef, 0x9f, 0x10,
    0x8a, 0x06, 0x05, 0xbd, 0x8d, 0x5d, 0xd4, 0x15, 0xfb, 0xe9, 0x43, 0x9e, 0x42, 0x8b, 0x5b, 0xee,
    0x0a, 0x0f, 0x1e, 0x00, 0x86, 0xed, 0x70, 0x72, 0xff, 0x38, 0xd5, 0x39, 0xd9, 0xa6, 0x54, 0x2e,
    0x67, 0xe7, 0x96, 0x91, 0xc5, 0x20, 0x4b, 0x1a, 0xba, 0x2a, 0xe0, 0x17, 0x0d, 0xc7, 0xa8, 0xa9,
    0x19, 0x07, 0xdd, 0x60, 0x26, 0xf5, 0x3b, 0x7e, 0x29, 0xc6, 0xfc, 0xf1, 0xdc, 0x85, 0x22, 0x11,
    0x24, 0x3d, 0x32, 0xa1, 0x2f, 0x30, 0x52, 0xe3, 0x16, 0xb9, 0x48, 0x64, 0x8c, 0x3f, 0x2c, 0x90,
    0x4e, 0xd1, 0xa2, 0x0b, 0x81, 0xde, 0x8e, 0xbf, 0x9d, 0x92, 0xcc, 0x46, 0x13, 0xb8, 0xf7, 0xaf,
    0x80, 0x93, 0x2d, 0x12, 0x99, 0x7d, 0x63, 0xbb, 0x78, 0x18, 0xb7, 0x9a, 0x6e, 0xe6, 0xcf, 0xe8,
    0x9b, 0x36, 0x09, 0x7c, 0xb2, 0x23, 0x94, 0x66, 0xbc, 0xca, 0xd0, 0xd8, 0x98, 0xda, 0x50, 0xf6,
    0xd6, 0xb0, 0x4d, 0x04, 0xb5, 0x88, 0x1f, 0x51, 0xea, 0x35, 0x74, 0x41, 0x1d, 0xd2, 0x56, 0x47,
    0x61, 0x0c, 0x14, 0x3c, 0x27, 0xc9, 0xe5, 0xb1, 0xdf, 0x73, 0xce, 0x37, 0xcd, 0xaa, 0x6f, 0xdb,
    0xf3, 0xc4, 0x34, 0x40, 0xc3, 0x25, 0x49, 0x95, 0x01, 0xb3, 0xe4, 0xc1, 0x84, 0xb6, 0x5c, 0x57};

uint8 S_BOX_I_0E[256] = {
    0x51, 0x7e, 0x1a, 0x3a, 0x3b, 0x1f, 0xac, 0x4b, 0x20, 0xad, 0x88, 0xf5, 0x4f, 0xc5, 0x26, 0xb5,
    0xde, 0x25, 0x45, 0x5d, 0xc3, 0x81, 0x8d, 0x6b, 0x03, 0x15, 0xbf, 0x95, 0xd4, 0x58, 0x49, 0x8e,
    0x75, 0xf4, 0x99, 0x27, 0xbe, 0xf0, 0xc9, 0x7d, 0x63, 0xe5, 0x97, 0x62, 0xb1, 0xbb, 0xfe, 0xf9,
    0x70, 0x8f, 0x94, 0x52, 0xab, 0x72, 0xe3, 0x66, 0xb2, 0x2f, 0x86, 0xd3, 0x30, 0x23, 0x02, 0xed,
    0x8a, 0xa7, 0xf3, 0x4e, 0x65, 0x06, 0xd1, 0xc4, 0x34, 0xa2, 0x05, 0xa4, 0x0b, 0x40, 0x5e, 0xbd,
    0x3e, 0x96, 0xdd, 0x4d, 0x91, 0x71, 0x04, 0x60, 0x19, 0xd6, 0x89, 0x67, 0xb0, 0x07, 0xe7, 0x79,
    0xa1, 0x7c, 0xf8, 0x00, 0x09, 0x32, 0x1e, 0x6c, 0xfd, 0x0f, 0x3d, 0x36, 0x0a, 0x68, 0x9b, 0x24,
    0x0c, 0x93, 0xb4, 0x1b, 0x80, 0x61, 0x5a, 0x1c, 0xe2, 0xc0, 0x3c, 0x12, 0x0e, 0xf2, 0x2d, 0x14,
    0x57, 0xaf, 0xee, 0xa3, 0xf7, 0x5c, 0x44, 0x5b, 0x8b, 0xcb, 0xb6, 0xb8, 0xd7, 0x42, 0x13, 0x84,
    0x85, 0xd2, 0xae, 0xc7, 0x1d, 0xdc, 0x0d, 0x77, 0x2b, 0xa9, 0x11, 0x47, 0xa8, 0xa0, 0x56, 0x22,
    0x87, 0xd9, 0x8c, 0x98, 0xa6, 0xa5, 0xda, 0x3f, 0x2c, 0x50, 0x6a, 0x54, 0xf6, 0x90, 0x2e, 0x82,
    0x9f, 0x69, 0x6f, 0xcf, 0xc8, 0x10, 0xe8, 0xdb, 0xcd, 0x6e, 0xec, 0x83, 0xe6, 0xaa, 0x21, 0xef,
    0xba, 0x4a, 0xea, 0x29, 0x31, 0x2a, 0xc6, 0x35, 0x74, 0xfc, 0xe0, 0x33, 0xf1, 0x41, 0x7f, 0x17,
    0x76, 0x43, 0xcc, 0xe4, 0x9e, 0x4c, 0xc1, 0x46, 0x9d, 0x01, 0xfa, 0xfb, 0xb3, 0x92, 0xe9, 0x6d,
    0x9a, 0x37, 0x59, 0xeb, 0xce, 0xb7, 0xe1, 0x7a, 0x9c, 0x55, 0x18, 0x73, 0x53, 0x5f, 0xdf, 0x78,
    0xca, 0xb9, 0x38, 0xc2, 0x16, 0xbc, 0x28, 0xff, 0x39, 0x08, 0xd8, 0x64, 0x7b, 0xd5, 0x48, 0xd0};

uint32 RC[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
                 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};

#define table1(REG1, s1, s2, s3, s4)                                                                        \
    {                                                                                                       \
        REG1[0] = S_BOX_02[s1], REG1[1] = S_BOX_01[s1], REG1[2] = S_BOX_01[s1], REG1[3] = S_BOX_03[s1];     \
        REG1[4] = S_BOX_02[s2], REG1[5] = S_BOX_01[s2], REG1[6] = S_BOX_01[s2], REG1[7] = S_BOX_03[s2];     \
        REG1[8] = S_BOX_02[s3], REG1[9] = S_BOX_01[s3], REG1[10] = S_BOX_01[s3], REG1[11] = S_BOX_03[s3];   \
        REG1[12] = S_BOX_02[s4], REG1[13] = S_BOX_01[s4], REG1[14] = S_BOX_01[s4], REG1[15] = S_BOX_03[s4]; \
    }

#define table2(REG2, s1, s2, s3, s4)                                                                        \
    {                                                                                                       \
        REG2[0] = S_BOX_03[s1], REG2[1] = S_BOX_02[s1], REG2[2] = S_BOX_01[s1], REG2[3] = S_BOX_01[s1];     \
        REG2[4] = S_BOX_03[s2], REG2[5] = S_BOX_02[s2], REG2[6] = S_BOX_01[s2], REG2[7] = S_BOX_01[s2];     \
        REG2[8] = S_BOX_03[s3], REG2[9] = S_BOX_02[s3], REG2[10] = S_BOX_01[s3], REG2[11] = S_BOX_01[s3];   \
        REG2[12] = S_BOX_03[s4], REG2[13] = S_BOX_02[s4], REG2[14] = S_BOX_01[s4], REG2[15] = S_BOX_01[s4]; \
    }

#define table3(REG3, s1, s2, s3, s4)                                                                        \
    {                                                                                                       \
        REG3[0] = S_BOX_01[s1], REG3[1] = S_BOX_03[s1], REG3[2] = S_BOX_02[s1], REG3[3] = S_BOX_01[s1];     \
        REG3[4] = S_BOX_01[s2], REG3[5] = S_BOX_03[s2], REG3[6] = S_BOX_02[s2], REG3[7] = S_BOX_01[s2];     \
        REG3[8] = S_BOX_01[s3], REG3[9] = S_BOX_03[s3], REG3[10] = S_BOX_02[s3], REG3[11] = S_BOX_01[s3];   \
        REG3[12] = S_BOX_01[s4], REG3[13] = S_BOX_03[s4], REG3[14] = S_BOX_02[s4], REG3[15] = S_BOX_01[s4]; \
    }

#define table4(REG4, s1, s2, s3, s4)                                                                        \
    {                                                                                                       \
        REG4[0] = S_BOX_01[s1], REG4[1] = S_BOX_01[s1], REG4[2] = S_BOX_03[s1], REG4[3] = S_BOX_02[s1];     \
        REG4[4] = S_BOX_01[s2], REG4[5] = S_BOX_01[s2], REG4[6] = S_BOX_03[s2], REG4[7] = S_BOX_02[s2];     \
        REG4[8] = S_BOX_01[s3], REG4[9] = S_BOX_01[s3], REG4[10] = S_BOX_03[s3], REG4[11] = S_BOX_02[s3];   \
        REG4[12] = S_BOX_01[s4], REG4[13] = S_BOX_01[s4], REG4[14] = S_BOX_03[s4], REG4[15] = S_BOX_02[s4]; \
    }

#define table(REG, s)                                                                                             \
    {                                                                                                             \
        REG[0] = S_BOX_01[s[0]], REG[1] = S_BOX_01[s[5]], REG[2] = S_BOX_01[s[10]], REG[3] = S_BOX_01[s[15]];     \
        REG[4] = S_BOX_01[s[4]], REG[5] = S_BOX_01[s[9]], REG[6] = S_BOX_01[s[14]], REG[7] = S_BOX_01[s[3]];      \
        REG[8] = S_BOX_01[s[8]], REG[9] = S_BOX_01[s[13]], REG[10] = S_BOX_01[s[2]], REG[11] = S_BOX_01[s[7]];    \
        REG[12] = S_BOX_01[s[12]], REG[13] = S_BOX_01[s[1]], REG[14] = S_BOX_01[s[6]], REG[15] = S_BOX_01[s[11]]; \
    }

#define rotword(word) ((word << 8) + (word >> 24))
__m128i KEY[11];

__m128i ssma(__m128i state, __m128i key)
{
    uint8 *s = (uint8 *)&state;
    uint8 REG1[16] = {0}, REG2[16] = {0}, REG3[16] = {0}, REG4[16] = {0};
    table1(REG1, s[0], s[4], s[8], s[12]);
    table2(REG2, s[5], s[9], s[13], s[1]);
    table3(REG3, s[10], s[14], s[2], s[6]);
    table4(REG4, s[15], s[3], s[7], s[11]);
    __m128i R1 = _mm_loadu_si128((__m128i *)REG1);
    __m128i R2 = _mm_loadu_si128((__m128i *)REG2);
    __m128i R3 = _mm_loadu_si128((__m128i *)REG3);
    __m128i R4 = _mm_loadu_si128((__m128i *)REG4);
    __m128i t1 = _mm_xor_si128(R1, R2);
    __m128i t2 = _mm_xor_si128(R3, R4);
    __m128i t3 = _mm_xor_si128(t1, t2);
    __m128i t4 = _mm_xor_si128(t3, key);
    return t4;
}

__m128i ssa(__m128i state, __m128i key)
{
    uint8 *s = (uint8 *)&state;
    uint8 REG1[16] = {0};
    table(REG1, s);
    __m128i R1 = _mm_loadu_si128((__m128i *)REG1);
    __m128i t1 = _mm_xor_si128(R1, key);
    return t1;
}

uint32 Key_Sub(uint32 w)
{
    uint8 byte = 0;
    uint32 result = 0, i = 0;
    for (i = 0; i < 4; i++)
    {
        byte = (w >> ((3 - i) * 8)) & 0xff;
        byte = S_BOX_01[byte];
        result = (result << 8) + byte;
    }
    return result;
}

void keygen(uint32 *key, int mode)
{
    int i = 0;
    uint32 w[44] = {0}, tmp = 0;
    w[0] = key[0], w[1] = key[1], w[2] = key[2], w[3] = key[3];
    for (int i = 4; i < 44; i++)
    {
        tmp = w[i - 1];
        if (i % 4 == 0)
            tmp = Key_Sub(rotword(w[i - 1])) ^ (RC[i / 4 - 1]);
        w[i] = tmp ^ w[i - 4];
    }
    for (i = 0; i < 11; i++)
        KEY[i] = _mm_set_epi32(w[4 * i], w[4 * i + 1], w[4 * i + 2], w[4 * i + 3]);
    return;
}

int main()
{
    int i = 0, j = 0;
    uint32 k[4] = {0x0f1571c9, 0x47d9e859, 0x0cb7add6, 0xaf7f6798};
    uint8 m[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};

    __m128i state = _mm_setr_epi8(0x0e, 0x36, 0x34, 0xae,
                                  0xce, 0x72, 0x25, 0xb6,
                                  0xf2, 0x6b, 0x17, 0x4e,
                                  0xd9, 0x2b, 0x55, 0x88);
    __m128i key = _mm_setr_epi8(0xdc, 0x90, 0x37, 0xb0,
                                0x9b, 0x49, 0xdf, 0xe9,
                                0x97, 0xfe, 0x72, 0x3f,
                                0x38, 0x81, 0x15, 0xa7);

    keygen(k, 1);
    for (i = 0; i < 11; i++)
    {
        uint8 *tmp = (uint8 *)&KEY[i];
        for (j = 0; j < 16; j++)
        {
            printf("%02x ", tmp[j]);
        }
        printf("\n");
    }

    clock_t start = clock();

    for (i = 0; i < 1000000; i++)
    {
        //state = ssa(state, key); //4.411 s
        //table1(m[0], m[1], m[2], m[3]); //0.558 s
        //R1 = _mm_load_si128((__m128i *)REG1); //0.149 s
        //t3 = _mm_xor_si128(t1, t2); //0.164 s
        keygen(k, 1);
    }

    clock_t end = clock();

    /*
    uint8 *r = (uint8 *)&state;
    for (j = 0; j < 16; j++)
        printf("%02x ", r[j]);
    printf("\n");
*/
    printf("time: %lf s", (double)(end - start) / CLOCKS_PER_SEC);
    system("pause");
    return 0;
}

//密文： ff0b844a0853bf7c6934ab4364148fb9