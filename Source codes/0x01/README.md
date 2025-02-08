# 🤔 What the HELL did I just stumble upon?
0x01 (hex code for 1) is a variation of the Wacatac, KillMBR and Generic trojan, that doesn't work on systems made after Windows XP, and doesn't activate on May 20th (for personal reasons).

This can:
- Overwrite the boot record (first 64 sectors)
- Add a registry key
- Copy itself to system directories
- Set itself as a critical process (failed)
- Hook and change window text to NULL
- Also exploits multiple vulnerabilities in the gdi32.dll and msimg32.dll critical files to display GDI.

> [!NOTE]
> The safe version doesn't destroy the PC, instead it only displays effects
>
> Password to the ZIP file: one

# ❤️ For skids
I know you may either say it's skidded or skid from it, so for that, I added a MIT licence to this malware, so you can't use my source code without my permission, and you must also leave a copyright notice when using my source code.
