; Stretch SSE main loop implement

;void horizontal_sse_iir_line(float *oTemp,  unsigned long* id, float *od, int width, int height, float *a0, float *a1, float *a2, float *a3 float *b1, float *b2, float *cprev, float *cnext);
			
BITS 32

SECTION .text			
global _horizontal_sse_iir_line

_horizontal_sse_iir_line:
	push ebp
	mov ebp, esp
	sub esp, 0x10;  
	push edi
	push esi
	push eax
	push ebx
	push ecx
	push edx

	%define otemp [dword ebp + 8] ; 
	%define id [dword ebp + 0x0c]
	%define od [dword ebp + 0x10]
	%define width [dword ebp + 0x14]
	%define height [dword ebp + 0x18]
	%define a0 [dword ebp+0x1c]
	%define a1 [dword ebp+0x20]
	%define a2 [dword ebp+0x24]
	%define a3 [dword ebp+0x28]
	%define b1 [dword ebp+0x2c]
	%define b2 [dword ebp+0x30]
	%define cprev [dword ebp+0x34]
	%define cnext [dword ebp+0x38]

	%define current_in [dword ebp - 0x10]

		mov eax, cprev;
		movups xmm1, [eax];
		shufps xmm1, xmm1, 0x00;

		mov esi, id;
		pmovzxbd xmm0, [esi];
		cvtdq2ps xmm0, xmm0;											xmm0: id[i];
		movups xmm2, xmm0;												xmm2: prevIn;
		mulps xmm0, xmm1;		
		movups xmm6, xmm0;												xmm6: prev2Out;
		movups xmm4, xmm0;												xmm4: prevOut;

		mov eax, a0;
		movups xmm1, [eax];
		shufps xmm1, xmm1, 0x00;										xmm1 : a0;

		mov eax, a1;
		movups xmm3, [eax];												
		shufps xmm3, xmm3, 0x00;										xmm3 : a1;

		mov eax, b1;
		movups xmm5, [eax]; 
		shufps xmm5, xmm5, 0x00;										xmm5 := b1;

		mov eax, b2;
		movups xmm7, [eax];
		shufps xmm7, xmm7, 0x00;										xmm7 := b2;

		mov edx, otemp;
		mov ecx, width;

loop_body_left_right_start:
			pmovzxbd xmm0, [esi];
			cvtdq2ps xmm0, xmm0;											xmm0: id[i]
			;movups current_in, xmm0;

			mulps xmm0, xmm1;													xmm0: id[i] * a0;
			mulps xmm2, xmm3;												xmm2: id[i-1] * a1;
			addps xmm0, xmm2;												xmm0: id[i] * a0 + id[i-1] * a1;
			movups xmm2, xmm4;												xmm2 = oTemp[i-1]
			mulps xmm2, xmm5;												xmm2 = oTemp[i-1] * b1;
			subps xmm0, xmm2;												xmm0: id[i] * a0 + id[i-1]*a1 - oTemp[i-1]*b1;
			movups xmm2, xmm6;												xmm2 = oTemp[i-2];
			mulps xmm2, xmm7;												xmm2 = oTemp[i-1] * b2;
			subps xmm0, xmm2;												xmm0: result: id[i] * a0 + id[i-1]*a1 - oTemp[i-1]*b1 - oTemp[i-2]*b2;

			movups [edx], xmm0;												oTemp = result;
			pmovzxbd xmm2, [esi];												
			cvtdq2ps xmm2, xmm2;											xmm2 = id[i]; for next round: xmm2 = id[i-1];
			;movups xmm2, current_in;
			movups xmm6, xmm4;												xmm6 = oTemp[i-1]; for next round: xmm6 = oTemp[i-2];
			movups xmm4, xmm0;												xmm4 = oTemp[i]; for next round: xmm4 = oTemp[i-1];

			add esi, 0x04;
			add edx, 0x10;
loop_body_left_right_end:
			dec ecx;
			jnz loop_body_left_right_start;

			sub esi, 0x04;
			sub edx, 0x10;

; ¿ªÊ¼´ÓÓÒÍù×ó
			mov eax, cnext;
			movups xmm1, [eax];
			shufps xmm1, xmm1, 0x00;						xmm1: cnext;

			pmovzxbd xmm0, [esi];
			cvtdq2ps xmm0, xmm0;							xmm0: id[i];

			movups xmm2, xmm0;								prevIn

			movups xmm4, xmm0;								
			mulps xmm4, xmm1;									prevOut;
			movups xmm6, xmm4;								prev2Out;

			mov eax, a2;
			movups xmm1, [eax];
			shufps xmm1, xmm1, 0x00;					xmm1 := a0;

			mov eax, a3;
			movups xmm3, [eax];
			shufps xmm3, xmm3, 0x00;					xmm3 := a1;

			;	od += 4*height*(width-1);
			mov edi, od;
			mov ecx, width;
			push ecx;
			mov EAX, height;
			imul EAX, 0x10;
			sub ecx, 1;
			imul ecx, eax;
			add edi, ecx;
			pop ecx; mov ecx, width;

	loop_body_right_left_start:
				movups current_in, xmm0;											currIn = xmm0;
				mulps xmm0, xmm1;													xmm0 = id[i+1] * a0;
				mulps xmm2, xmm3;												xmm2 = id[i+2] * a1;
				addps xmm0, xmm2;												xmm0 = id[i+1] * a0 + id[i+2] * a1;
				movups xmm2, xmm4;												xmm2 = od[i+1];
				mulps xmm2, xmm5;												xmm2 = od[i+1] * b1;
				subps xmm0, xmm2;												xmm0 = id[i+1] * a0 + id[i+2] * a1 - od[i+1] * b1;
				movups xmm2, xmm6;												xmm2 = od[i+2];
				mulps xmm2, xmm7;												xmm2 = od[i+2] * b2;
				subps xmm0, xmm2;												xmm0 = id[i+1] * a0 + id[i+2] * a1 - od[i+1] * b1 - od[i+2] * b2;

				movups xmm6, xmm4;												xmm6 = xmm4 = od[i+1] ->next round->od[i+2];
				movups xmm4, xmm0;												xmm4 = xmm0 = od[i] -> next round->od[i+1];

				movups xmm2, [EDX];
				addps xmm0, xmm2;												xmm0 = oTemp[i] + id[i+1] * a0 + id[i+2] * a1 - od[i+1] * b1 - od[i+2] * b2;
				movups [edi], xmm0;												od[i] = xmm0;

				pmovzxbd xmm0, [esi];
				cvtdq2ps xmm0, xmm0;											xmm0: id[i] ->next round -> id[i+1]
				movups xmm2, current_in;											xmm2 = currIn = id[i+1] ->next round->id[i+2];
				sub esi, 0x04;
				sub edi, EAX;
				sub EDX, 0x10;
	loop_body_right_left_end:
				dec ecx;
				jnz loop_body_right_left_start;

	pop edx
	pop ecx
	pop ebx
	pop eax
	pop esi
	pop edi

	emms
	leave 
	ret 