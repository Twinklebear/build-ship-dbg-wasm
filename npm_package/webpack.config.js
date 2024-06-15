const path = require("path");

module.exports = {
  entry: "./src/index.ts",
  mode: "development",
  devtool: "inline-source-map",
  target: "web",
  output: {
    filename: "index.js",
    path: path.resolve(__dirname, "dist"),
    globalObject: "this",
    library: {
      name: "npm_package",
      type: "umd",
    },
  },
  module: {
    rules: [
      {
        // Note: using asset/inline will allow bundling it
        // into the js file so it doesn't need to be copied, but
        // it gets turned into a base64 encoded string which is
        // terrible for compile time
        test: /\.wasm$/i,
        type: "asset/resource",
      },
      {
        test: /\.tsx?$/,
        use: "ts-loader",
        exclude: /node_modules/,
      },
    ],
  },
  resolve: {
    extensions: [".tsx", ".ts", ".js"],
  },
};
