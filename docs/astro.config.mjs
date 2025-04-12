// @ts-check
import { defineConfig } from "astro/config";
import starlight from "@astrojs/starlight";

// https://astro.build/config
export default defineConfig({
	integrations: [
		starlight({
			title: "RoboFut",
			// social: [
			// 	{
			// 		icon: "github",
			// 		label: "GitHub",
			// 		href: "https://github.com/withastro/starlight",
			// 	},
			// ],
			sidebar: [
				{
					label: "Guides",
					translations: {
						es: "Guías",
					},
					items: [
						{
							label: "Features",
							slug: "guides/features",
							translations: {
								es: "Características",
							},
						},
						{
							label: "HBridge",
							slug: "guides/hbridge",
							translations: {
								es: "Puentes H",
							},
						},
						{ label: "PinOut", slug: "guides/pinout" },
						{
							label: "Controls",
							slug: "guides/controls",
							translations: {
								es: "Controles",
							},
						},
					],
				},
			],
			customCss: ["./src/styles/index.css"],
			defaultLocale: "en",
			locales: {
				en: {
					label: "English",
					lang: "en",
				},
				es: {
					label: "Español",
					lang: "es",
				},
			},
		}),
	],
});
