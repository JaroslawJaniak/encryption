import { useState } from "react";

type CharData = {
  char: string;
  count: number;
  freq: number;
};

type CharCount = {
  [key: number]: CharData;
};

function UploadForm() {
  const [fileContent, setFileContent] = useState<string>("");

  const alfabet = [
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ".",
    ",",
    ";",
    ":",
    "!",
    "?",
    '"',
    "@",
    "#",
    "$",
    "%",
    "^",
    "&",
    "*",
    "_",
    "(",
    ")",
    "[",
    "]",
    "{",
    "}",
    "\\",
    "|",
    "/",
    "<",
    ">",
    "+",
    "-",
    "=",
  ];
  const T: { [key: number]: string } = {};
  for (let i = 0; i < alfabet.length; i++) {
    T[alfabet[i].charCodeAt(0)] = alfabet[i];
  }

  // Function to analyze the text and count character occurrences
  // Returns an object where keys are character codes and values are their counts
  // Example: { 65: 3, 66: 2 } means 'A' appeared 3 times and 'B' appeared 2 times
  // This function can be used to analyze the content of the uploaded file
  // It iterates through each character in the text, gets its character code, and updates the count in the charCount object
  //{65: 3, char: 'A', count: 3, freq: 0.3}

  // function textAnalyzer(text: string): { [key: number]: number } {
  //   const charCount: { [key: number]: number } = {};
  //   for (let i = 0; i < text.length; i++) {
  //     const charCode = text.charCodeAt(i);
  //     charCount[charCode] = (charCount[charCode] || 0) + 1;
  //   }
  //   return charCount;
  // }

  function textAnalyzer(text: string): CharCount {
    const charCount: CharCount = {};

    for (let i = 0; i < text.length; i++) {
      const charCode = text.charCodeAt(i);
      const char = text[i];

      if (!charCount[charCode]) {
        charCount[charCode] = {
          char: char,
          count: 0,
          freq: 0,
        };
      }

      charCount[charCode].count++;
    }

    // Obliczenie częstotliwości występowania
    for (const key in charCount) {
      charCount[key].freq = charCount[key].count / text.length;
    }

    return charCount;
  }

  const handleFileChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    const file = event.target.files?.[0];

    if (!file) return;

    const reader = new FileReader();

    reader.onload = () => {
      setFileContent(reader.result as string);
    };

    reader.readAsText(file);
  };

  return (
    <div className="w-full space-y-6 rounded border border-neutral-400 bg-neutral-300 p-5 text-neutral-200 shadow-xl">
      {/* File upload */}
      <section className="rounded-md border border-neutral-400 bg-neutral-200 p-4">
        <div className="mb-3 flex items-center gap-2">
          <span className="text-xl">📄</span>
          <h3 className="font-semibold text-neutral-900">Text file import</h3>
        </div>

        <input
          type="file"
          accept=".txt,text/plain"
          onChange={handleFileChange}
          className="block w-full cursor-pointer rounded-md border border-neutral-600 bg-neutral-900 text-sm text-neutral-300
        file:mr-4 file:cursor-pointer file:border-0
        file:bg-neutral-600 file:px-4 file:py-2.5
        file:font-medium file:text-white
        hover:file:bg-neutral-500"
        />
      </section>

      {/* Text preview */}
      <section className="space-y-3">
        <h3 className="border-b border-neutral-700 pb-2 text-sm font-semibold uppercase tracking-wider text-neutral-900">
          Source text
        </h3>

        <textarea
          value={fileContent}
          readOnly
          rows={10}
          className="w-full resize-y rounded-md border border-neutral-700 bg-neutral-200 p-4 font-mono text-sm leading-relaxed text-neutral-800 outline-none focus:border-neutral-500"
        />
      </section>

      {/* Data panels */}
      <section className="space-y-3">
        <h3 className="border-b border-neutral-700 pb-2 text-sm font-semibold uppercase tracking-wider text-neutral-900">
          Data structures
        </h3>

        <div className="grid grid-cols-1 gap-4 lg:grid-cols-3">
          {/* <div className="space-y-2 rounded border border-neutral-700 bg-neutral-200 p-3">
            <h4 className="text-xs font-semibold uppercase tracking-wide text-neutral-400">
              Character table
            </h4>
            <textarea
              value={Object.values(T).join("\n")}
              readOnly
              rows={10}
              className="w-full resize-y rounded-md border border-neutral-700 bg-neutral-950 p-3 font-mono text-xs text-emerald-300 outline-none"
            />
          </div>

          <div className="space-y-2 rounded-md border border-neutral-700 bg-neutral-800 p-3">
            <h4 className="text-xs font-semibold uppercase tracking-wide text-neutral-400">
              Table object
            </h4>
            <textarea
              value={JSON.stringify(T, null, 2)}
              readOnly
              rows={10}
              className="w-full resize-y rounded-md border border-neutral-700 bg-neutral-950 p-3 font-mono text-xs text-sky-300 outline-none"
            />
          </div>

          <div className="space-y-2 rounded-md border border-neutral-700 bg-neutral-800 p-3">
            <h4 className="text-xs font-semibold uppercase tracking-wide text-neutral-400">
              Analysis JSON
            </h4>
            <textarea
              value={JSON.stringify(textAnalyzer(fileContent), null, 2)}
              readOnly
              rows={10}
              className="w-full resize-y rounded-md border border-neutral-700 bg-neutral-950 p-3 font-mono text-xs text-amber-300 outline-none"
            />
          </div> */}
        </div>
      </section>

      {/* Character analysis */}
      <section className="space-y-4 rounded-md border border-neutral-700 bg-neutral-700 p-4">
        <div className="flex flex-wrap items-center justify-between gap-3">
          <h3 className="text-lg font-semibold text-neutral-100">
            Character Analysis
          </h3>

          <div className="rounded-md border border-neutral-500/30 bg-neutral-950 px-4 py-2">
            <span className="text-xs text-neutral-200">Total characters</span>
            <div className="text-xl font-bold tabular-nums text-neutral-400">
              {fileContent.length.toLocaleString()}
            </div>
          </div>
        </div>

        <div className="overflow-x-auto rounded-md border border-neutral-800">
          <table className="w-full border-collapse text-sm">
            <thead>
              <tr className="bg-neutral-800 text-left text-xs uppercase tracking-wider text-neutral-400">
                <th className="px-4 py-3">Character</th>
                <th className="px-4 py-3 text-center">Count</th>
                <th className="px-4 py-3 text-right">Frequency</th>
              </tr>
            </thead>

            <tbody>
              {Object.entries(textAnalyzer(fileContent)).map(
                ([charCode, data]) => (
                  <tr
                    key={charCode}
                    className="border-t border-neutral-800 transition-colors hover:bg-neutral-600/50"
                  >
                    <td className="px-4 py-3 font-mono font-semibold text-green-300">
                      "{data.char}"
                    </td>

                    <td className="px-4 py-3 text-center tabular-nums text-neutral-300">
                      {data.count}
                    </td>

                    <td className="px-4 py-3 text-right">
                      <span className="font-mono tabular-nums text-amber-400">
                        {data.freq.toFixed(2)}
                      </span>
                      <span className="ml-2 text-xs text-neutral-400">
                        /{(data.freq * 100).toFixed(1)}%
                      </span>
                    </td>
                  </tr>
                ),
              )}
            </tbody>
          </table>
        </div>
      </section>
    </div>
  );
}

export default UploadForm;
