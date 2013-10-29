;void vertical_mmx_fir_line(__int32 radius, __int32 scanLengthInBytes, __int32 height, __int16 *weightInt, unsigned long *lpPixelBufferDest, unsigned long *lpPixelBufferLine);

BITS 32

SECTION .text			
global _vertical_mmx_fir_line


_vertical_mmx_fir_line:

	push ebp
	mov ebp, esp
	sub esp, 0x10;  
	push edi
	push esi
	push eax
	push ecx
	push edx

	%define radius [dword ebp + 8] ; 
	%define scanLengthInBytes [dword ebp + 0x0c]
	%define height [dword ebp + 0x10]
	%define weightInt [dword ebp + 0x14]
	%define lpPixelBufferDest [dword ebp + 0x18]
	%define lpPixelBufferLine [dword ebp+0x1c]

	%define diameter [dword ebp - 0x04]

			mov edi, lpPixelBufferDest;
			mov ecx, radius;
			sal ecx, 1;
			add ecx, 1;
			mov diameter, ecx;
			mov ecx, radius;

border_bottom_loop_start:
			mov eax, weightInt;
			pxor mm2, mm2;

			mov edx, height;
			sub edx, radius;
			sub edx, radius;
			sub edx, 1;
			add edx, ecx;
			sal edx, 2;

			mov esi, lpPixelBufferLine;
			add esi, edx; // esi := lpPixelBufferLine + 4 * (height - radius - radius - 1 + ecx)

			mov edx, diameter;
			sub edx, ecx;

.no_corr_loop_start:
		 	pxor mm0, mm0;
		 	movd mm0, [esi];
		 	pxor mm1, mm1;
		 	punpcklbw mm0, mm1; 

		 	movd mm1, [eax];
		 	pshufw mm1, mm1, 0x00; 
		 	pmullw mm1, mm0;
		 	paddw mm2, mm1;
.no_corr_loop_end:

			add eax, 2;
			add esi, 4;	// esi += 4;
			dec edx;
			jnz .no_corr_loop_start;
			;// esi = lpPixelBufferLine + 4 (height - radius  - 2 + ecx) 

			mov edx, height;
			sub edx, 1;
			sal edx, 2;
			mov esi, lpPixelBufferLine;
			add esi, edx; // esi = lpPixelBufferLine + 4*(height-1)

			mov edx, ecx;

			pxor mm0, mm0;
			movd mm0, [esi];
			pxor mm1, mm1;
			punpcklbw mm0, mm1; 

.corr_loop_start:
		 	movd mm1, [eax];
		 	pshufw mm1, mm1, 0x00; 
		 	pmullw mm1, mm0;
		 	paddw mm2, mm1;
.corr_loop_end:

			add eax, 2;
			dec edx;
			jnz .corr_loop_start; 

			psrlw mm2, 8;
			packuswb mm2, mm2;
			movd [edi], mm2;

			sub edi, scanLengthInBytes;
border_bottom_loop_end:
			dec ecx;
			jnz border_bottom_loop_start;

			mov ecx, height;
			sub ecx, radius;
			sub ecx, radius;
mid_loop_start:
			mov eax, weightInt;
			pxor mm2, mm2;

			mov edx, ecx;
			sub edx, 1;
			sal edx, 2;

			mov esi, lpPixelBufferLine;
			add esi, edx;

			mov edx, radius;
			add edx, radius;
			add edx, 1;
.no_corr_loop_start:
		 	pxor mm0, mm0;
		 	movd mm0, [esi];
		 	pxor mm1, mm1;
		 	punpcklbw mm0, mm1; 

		 	movd mm1, [eax];
		 	pshufw mm1, mm1, 0x00; 
		 	pmullw mm0, mm1;
		 	paddw mm2, mm0;
.no_corr_loop_end:
			add eax, 2;
			add esi, 4;
			dec edx;
			jnz .no_corr_loop_start;

			psrlw mm2, 8;
			packuswb mm2, mm2;
			movd [edi], mm2;
			sub edi, scanLengthInBytes;
mid_loop_end:
			dec ecx;
			jnz mid_loop_start;

			mov ecx, radius;
border_top_loop_start:
			mov eax, weightInt;
			pxor mm2, mm2;

			mov edx, radius;
			add edx, 1;
			sub edx, ecx;

			mov esi, lpPixelBufferLine;
			pxor mm0, mm0;
			movd mm0, [esi];
			pxor mm1, mm1;
			punpcklbw mm0, mm1; 
.corr_loop_start:
		 	movd mm1, [eax];
		 	pshufw mm1, mm1, 0x00; 
		 	pmullw mm1, mm0;
		 	paddw mm2, mm1;
.corr_loop_end:
			add eax, 2;
			dec edx;
			jnz .corr_loop_start;

			mov edx, ecx;
			add edx, radius;
.no_corr_loop_start:
		 	pxor mm0, mm0;
		 	movd mm0, [esi];
		 	pxor mm1, mm1;
		 	punpcklbw mm0, mm1; 

		 	movd mm1, [eax];
		 	pshufw mm1, mm1, 0x00; 
		 	pmullw mm1, mm0;
		 	paddw mm2, mm1;
.no_corr_loop_end:
			add eax, 2;
			add esi, 4;
			dec edx;
			jnz .no_corr_loop_start;


			psrlw mm2, 8;
			packuswb mm2, mm2;
			movd [edi], mm2;
			sub edi, scanLengthInBytes;
border_top_loop_end:
			dec ecx;
			jnz border_top_loop_start;

	pop edx
	pop ecx
	pop eax
	pop esi
	pop edi

	emms
	leave 
	ret 