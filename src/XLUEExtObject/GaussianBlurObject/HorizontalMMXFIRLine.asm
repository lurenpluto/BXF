; /********************************************************************
; /* Copyright (c) 2013 The BOLT UIEngine. All rights reserved.
; /* Use of this source code is governed by a BOLT license that can be
; /* found in the LICENSE file.
; ********************************************************************/ 
;void Horizontal_mmx_fir_line(int radius, int width, int heightInBytes, int *weightInt, unsigned long *lpPixelBufferTemp, unsigned long *lpPixelBufferLine);
			
BITS 32

SECTION .text			
global _Horizontal_mmx_fir_line

_Horizontal_mmx_fir_line:
	push ebp
	mov ebp, esp
	sub esp, 0x10;  
	push edi
	push esi
	push eax
	push ebx
	push ecx
	push edx

	%define radius [dword ebp + 8] ; 
	%define width [dword ebp + 0x0c]
	%define heightInBytes [dword ebp + 0x10]
	%define weightInt [dword ebp + 0x14]
	%define lpPixelBufferTemp [dword ebp + 0x18]
	%define lpPixelBufferLine [dword ebp+0x1c]

	mov edi, lpPixelBufferTemp;
;for (int col =bmp.Width - 1; col >= bmp.Width - radius; col--)
			mov ecx, radius;
border_right_loop_start:
				mov edx, ecx; 
				add edx, width;
				sub edx, 1;
				sub edx, radius; 
				sub edx, radius;
				sal edx, 2;
				
				mov esi, lpPixelBufferLine; 
				add esi, edx; 

				mov edx, radius;
				sal edx, 1;
				add edx, 1;
				sub edx, ecx;

				mov eax, weightInt;
				pxor mm2, mm2;
.start_loop_h_right:
				pxor mm0, mm0;
				movd mm0, [esi];
				pxor mm1, mm1
				PUNPCKLBW mm0, mm1;

				movd mm1, [eax];
				pshufw mm1, mm1, 0x00; 
				pmullw mm0, mm1;

				paddw mm2, mm0;
.end_loop_h_right:
				add eax, 2;
				add esi, 4;
				dec edx;
				jnz .start_loop_h_right;

				mov edx, ecx;

				sub esi, 0x04;
				pxor mm0, mm0;
				movd mm0, [esi];
				pxor mm1, mm1
				PUNPCKLBW mm0, mm1;
.start_loop_h_right_2:
				movd mm1, [eax];
				pshufw mm1, mm1, 0x00; 
				pmullw mm1, mm0;
				paddw mm2, mm1;
.end_loop_h_right_2:
				add eax, 2;
				dec edx;
				jnz .start_loop_h_right_2;

				psrlw mm2, 8;
				packuswb mm2, mm2;
				movd [edi], mm2;

				sub edi, heightInBytes;
border_right_loop_end:
			dec ecx; 
			jnz border_right_loop_start;

;for (int col = bmp.Width - radius - 1; col >= radius; col--)
			mov ecx, width;
			sub ecx, radius;
			sub ecx, radius;
mid_loop_start:
				mov edx, ecx;
				sub edx, 1;
				sal edx, 2; 
				mov esi, lpPixelBufferLine; 
				add esi, edx; 

				mov edx, radius;
				sal edx, 1;
				add edx, 1;

				mov eax, weightInt;
				pxor mm2, mm2;
.start_loop_h_mid:
				pxor mm0, mm0;
				movd mm0, [esi];
				pxor mm1, mm1
				PUNPCKLBW mm0, mm1;

				movd mm1, [eax];
				pshufw mm1, mm1, 0x00;
				pmullw mm0, mm1;

				paddw mm2, mm0;
.end_loop_h_mid:
				add eax, 2;
				add esi, 4;
				dec edx;
				jnz .start_loop_h_mid;

				psrlw mm2, 8;
				packuswb mm2, mm2;
				movd [edi], mm2;

				sub edi, heightInBytes;
mid_loop_end:
			dec ecx;
			jnz mid_loop_start;
;for (int col = radius - 1; col >= 0; col--)
			mov ecx, radius;
border_left_loop_start:
				mov esi, lpPixelBufferLine; 

				mov edx, radius;
				add edx, 1;
				sub edx, ecx;

				pxor mm2, mm2;
				pxor mm0, mm0;
				movd mm0, [esi];
				pxor mm1, mm1
				PUNPCKLBW mm0, mm1;

				mov eax, weightInt;
.start_loop_h_left_2:
				movd mm1, [eax];
				pshufw mm1, mm1, 0x00; 
				pmullw mm1, mm0;
				paddw mm2, mm1;
.end_loop_h_left_2:
				add eax, 2;
				dec edx;
				jnz .start_loop_h_left_2;

				mov edx, radius;
				add edx, ecx;
.start_loop_h_left:
				pxor mm0, mm0;
				movd mm0, [esi];
				pxor mm1, mm1
				PUNPCKLBW mm0, mm1;

				movd mm1, [eax];
				pshufw mm1, mm1, 0x00; 
				pmullw mm1, mm0;

				paddw mm2, mm1;
.end_loop_h_left:
				add eax, 2;
				add esi, 4;
				dec edx;
				jnz .start_loop_h_left;

				psrlw mm2, 8;
				packuswb mm2, mm2;
				movd [edi], mm2;
				sub edi, heightInBytes;
border_left_loop_end:
			dec ecx;
			jnz border_left_loop_start;

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esi
	pop edi

	emms
	leave 
	ret 